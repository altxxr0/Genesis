file(GLOB_RECURSE GAME_HEADERS CONFIGURE_DEPENDS include/*.h)
file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS src/*.cpp)

add_executable(GenesisGame ${GAME_HEADERS} ${GAME_SOURCES})
target_include_directories(GenesisGame PRIVATE include)

target_link_libraries(GenesisGame PRIVATE GenesisEngine)
