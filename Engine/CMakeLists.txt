file(GLOB_RECURSE ENGINE_HEADERS CONFIGURE_DEPENDS include/*.h)
file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS src/*.cpp)

add_library(GenesisEngine STATIC ${ENGINE_HEADERS} ${ENGINE_SOURCES})
target_include_directories(GenesisEngine PUBLIC include)