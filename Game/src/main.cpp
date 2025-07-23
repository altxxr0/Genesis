#include "Engine/Engine.h"
#include "Engine/Log.h"
#include "Platform/SDLWindow.h"
#include <stdexcept>
#include <iostream>

int main(int argc, char* argv[]) {

    Engine::LogInit();
    LOG_INFO("Initializing...");

    // - Default - //
    int width = 800;
    int height = 600;
    std::string title = "Genesis Game";
    bool fullscreen = false;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--fullscreen") {
            fullscreen = true;
            LOG_INFO("Set to fullscreen mode [--fullscreen]");
        } else if (arg == "--width" && i + 1 < argc) {
            try {
                width = std::stoi(argv[++i]);
                if (width <= 0) throw std::invalid_argument("Width must be positive");
                LOG_ERROR("Set width to " + std::to_string(width) + " [--width " + std::to_string(width) + "]");
            } catch (const std::exception& e) {
                std::cerr << "Error: Invalid width" << std::endl;
                LOG_ERROR("Invalid width argument: " + std::string(e.what()));
                return 1;
            }
        } else if (arg == "--height" && i + 1 < argc) {
            try {
                height = std::stoi(argv[++i]);
                if (height <= 0) throw std::invalid_argument("Height must be positive");
                LOG_ERROR("Set height to " + std::to_string(height) + " [--height " + std::to_string(height) + "]");
            } catch (const std::exception& e) {
                std::cerr << "Error: Invalid height" << std::endl;
                LOG_ERROR("Invalid height argument: " + std::string(e.what()));
                return 1;
            }
        } else if (arg == "--title" && i + 1 < argc) {
            title = argv[++i];
        } else {
            std::cerr << "Usage: " << argv[0] << " [--width W] [--height H] [--title T] [--fullscreen]" << std::endl;
            return 1;
        }
    }

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        LOG_ERROR("SDL Initialization failed: " + std::string(SDL_GetError()));
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        title.c_str(),
        width,
        height,
        fullscreen ? SDL_WINDOW_FULLSCREEN : 0
    );

    if (!window) {
        LOG_ERROR("Failed to create SDL window: " + std::string(SDL_GetError()));
        SDL_Quit();
        return 1;
    }

        LOG_INFO("Engine Initialized");
    bool done = false;
    SDL_Event event;
    while (!done) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                done = true;
            }
        }
        SDL_Delay(10);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}