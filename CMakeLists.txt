# CMakeLists.txt (Main)
cmake_minimum_required(VERSION 3.16)
project(GenesisEngine VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output folders
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Add external dependencies and subprojects
add_subdirectory(External/SDL)
add_subdirectory(Engine)
add_subdirectory(Game)