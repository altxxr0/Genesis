add_executable(Game
    src/main.cpp
)

target_include_directories(Game PRIVATE
    ${CMAKE_SOURCE_DIR}/Engine/include
)

add_library(Engine
    src/Engine.cpp
    src/SDLWindow.cpp
    src/Physics/Physics.cpp 
)


target_link_libraries(Game PRIVATE Engine)
