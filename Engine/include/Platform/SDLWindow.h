// Engine/include/Platform/SDLWindow.h
#pragma once
#include <SDL3/SDL.h>
#include <string>

namespace Engine {
    class SDLWindow {
    public:
        SDLWindow(const std::string& title, int width, int height);
        ~SDLWindow();
        bool ShouldClose() const;
        void PollEvents();
        SDL_Window* GetSDLWindow() const;

    private:
        SDL_Window* m_Window;
        bool m_ShouldClose;
    };
}