# Game/CMakeLists.txt
file(GLOB_RECURSE GAME_HEADERS CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
)
file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)
# Game/CMakeLists.txt
file(GLOB_RECURSE GAME_HEADERS CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
)
file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_executable(GenesisGame ${GAME_HEADERS} ${GAME_SOURCES})

target_include_directories(GenesisGame PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/Engine/include
    ${CMAKE_SOURCE_DIR}/External/SDL/include
    ${CMAKE_SOURCE_DIR}/External/Json/include
)

target_link_libraries(GenesisGame PRIVATE GenesisEngine SDL3::SDL3)
target_link_libraries(GenesisGame PRIVATE GenesisEngine SDL3::SDL3)