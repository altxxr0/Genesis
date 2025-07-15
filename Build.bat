@echo off
echo [Genesis Build] Starting build process...

set BUILD_DIR=Build

if not exist %BUILD_DIR% (
    mkdir %BUILD_DIR%
)

echo [Genesis Build] Configuring CMake...
cd %BUILD_DIR%
cmake ..

if errorlevel 1 (
    echo [Genesis Build] CMake configuration failed.
    exit /b 1
)

echo [Genesis Build] Building project...
cmake --build . --config Release

if exist bin\Release\GenesisGame.exe (
    echo [Genesis Build] Build complete. Launching game...
    bin\Release\GenesisGame.exe
) else (
    echo [Genesis Build] Build succeeded, but executable not found.
)

cd ..   
