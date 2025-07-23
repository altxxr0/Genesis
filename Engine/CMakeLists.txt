# Engine/CMakeLists.txt
file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)
file(GLOB_RECURSE ENGINE_HEADERS CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
)

add_library(GenesisEngine STATIC ${ENGINE_SOURCES} ${ENGINE_HEADERS})

target_include_directories(GenesisEngine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/External/SDL/include
    ${CMAKE_SOURCE_DIR}/External/Json/include
)

target_link_libraries(GenesisEngine PRIVATE SDL3::SDL3)