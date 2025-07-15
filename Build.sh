#!/bin/bash
echo "[Genesis Build] Starting build process..."

BUILD_DIR="Build"

if [ ! -d "$BUILD_DIR" ]; then
    mkdir "$BUILD_DIR"
fi

echo "[Genesis Build] Configuring CMake..."
cd "$BUILD_DIR"
cmake ..

if [ $? -ne 0 ]; then
    echo "[Genesis Build] CMake configuration failed."
    exit 1
fi

echo "[Genesis Build] Building project..."
cmake --build . --config Release

if [ -f "bin/Release/GenesisGame" ]; then
    echo "[Genesis Build] Build complete. Launching game..."
    ./bin/Release/GenesisGame
else
    echo "[Genesis Build] Build succeeded, but executable not found."
fi

cd ..
