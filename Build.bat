@echo off
setlocal
set CURRENT_DIR=%cd%

echo [Genesis Build] Cloning SDL3...

REM Only add submodule if not already added
if not exist External\SDL (
    git submodule add https://github.com/libsdl-org/SDL.git External/SDL
) else (
    echo [Genesis Build] SDL submodule already exists.
)

REM Kill possible interfering Git processes (if needed)
taskkill /F /IM Code.exe >nul 2>&1
taskkill /F /IM git-gui.exe >nul 2>&1
taskkill /F /IM git.exe >nul 2>&1
taskkill /F /IM git-bash.exe >nul 2>&1
taskkill /F /IM gitk.exe >nul 2>&1

REM Build SDL3 (Static)
echo [Genesis Build] Building SDL3 (static)...
cmake -B External/SDL/build -S External/SDL -DSDL_STATIC=ON -DSDL_SHARED=OFF -DSDL_TEST=OFF
cmake --build External/SDL/build --config Release

REM Ensure main Build directory exists
if not exist Build (
    mkdir Build
)

echo [Genesis Build] Configuring Genesis CMake...
cd Build
cmake .. -DSDL_STATIC=ON -DSDL_SHARED=OFF

if errorlevel 1 (
    echo [Genesis Build] CMake configuration failed.
    exit /b 1
)

echo [Genesis Build] Building Genesis Game...
cmake --build . --config Release

REM Run the built game if successful
if exist bin\Release\GenesisGame.exe (
    echo [Genesis Build] Build complete. Launching game...
    bin\Release\GenesisGame.exe
) else (
    echo [Genesis Build] Build succeeded, but executable not found.
)

cd %CURRENT_DIR%
endlocal
