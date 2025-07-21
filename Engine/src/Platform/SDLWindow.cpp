// Engine/src/Platform/SDLWindow.cpp
#include "Platform/SDLWindow.h"
#include <SDL3/SDL.h>

namespace Engine {
    SDLWindow::SDLWindow(const std::string& title, int width, int height) : m_ShouldClose(false) {
        // Initialize SDL with video subsystem
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
            m_ShouldClose = true;
            return;
        }

        // Create window with basic flags (resizable for flexibility)
        m_Window = SDL_CreateWindow(title.c_str(), width, height, SDL_WINDOW_RESIZABLE);
        if (!m_Window) {
            SDL_Log("Failed to create window: %s", SDL_GetError());
            m_ShouldClose = true;
        }
    }

    SDLWindow::~SDLWindow() {
        if (m_Window) {
            SDL_DestroyWindow(m_Window);
        }
        SDL_Quit();
    }

    bool SDLWindow::ShouldClose() const {
        return m_ShouldClose;
    }

    void SDLWindow::PollEvents() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                m_ShouldClose = true;
            }
        }
    }

    SDL_Window* SDLWindow::GetSDLWindow() const {
        return m_Window;
    }
}