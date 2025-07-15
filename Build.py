import os
import subprocess
import sys

BUILD_DIR = "Build"
GAME_EXECUTABLE = os.path.join("bin", "Release", "GenesisGame.exe") if os.name == 'nt' else os.path.join("bin", "Release", "GenesisGame")

print("[Genesis Build] Starting build process...")

if not os.path.exists(BUILD_DIR):
    os.makedirs(BUILD_DIR)

print("[Genesis Build] Configuring CMake...")
try:
    subprocess.check_call(["cmake", ".."], cwd=BUILD_DIR)
except subprocess.CalledProcessError:
    print("[Genesis Build] CMake configuration failed.")
    sys.exit(1)

print("[Genesis Build] Building project...")
try:
    subprocess.check_call(["cmake", "--build", ".", "--config", "Release"], cwd=BUILD_DIR)
except subprocess.CalledProcessError:
    print("[Genesis Build] Build failed.")
    sys.exit(1)

game_path = os.path.join(BUILD_DIR, GAME_EXECUTABLE)
if os.path.exists(game_path):
    print("[Genesis Build] Build complete. Launching game...")
    subprocess.run([game_path])
else:
    print("[Genesis Build] Build succeeded, but executable not found.")
