// Engine.h
#pragma once
#include <SDL3/SDL.h>
#include <string>

namespace Engine {

class Engine {
public:
    Engine();
    ~Engine();

    bool Init(int width, int height, const std::string& title, bool fullscreen = false);
    bool InitFromArgs(int argc, char* argv[]);
    SDL_Window* GetWindow() const;

private:
    SDL_Window* window;
    bool sdl_initialized;
};

bool Initialize(int argc, char* argv[]);
void Shutdown();

extern Engine* g_Engine;

} // namespace Engine