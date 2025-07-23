// Engine.cpp
#include "Engine/Engine.h"
#include "Engine/Log.h"
#include <nlohmann/json.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

namespace Engine {

Engine* g_Engine = nullptr;

// Internal default configuration
namespace {
    const int DEFAULT_WIDTH = 800;
    const int DEFAULT_HEIGHT = 600;
    const std::string DEFAULT_TITLE = "Genesis Engine";
    const bool DEFAULT_FULLSCREEN = false;
    const std::string CONFIG_FILE_PATH = "Override.json";
}

Engine::Engine() : window(nullptr), sdl_initialized(false) {}

Engine::~Engine() {
    if (window) {
        SDL_DestroyWindow(window);
    }
    if (sdl_initialized) {
        SDL_Quit();
    }
}

bool Engine::Init(int width, int height, const std::string& title, bool fullscreen) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        LOG_ERROR("Error initializing SDL: {}", SDL_GetError());
        return false;
    }
    sdl_initialized = true;

    Uint32 flags = fullscreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_RESIZABLE;
    window = SDL_CreateWindow(title.c_str(), width, height, flags);
    if (!window) {
        LOG_ERROR("Error creating window: {}", SDL_GetError());
        sdl_initialized = false;
        SDL_Quit();
        return false;
    }

    return true;
}

bool Engine::InitFromArgs(int argc, char* argv[]) {
    // Initialize with internal defaults
    int width = DEFAULT_WIDTH;
    int height = DEFAULT_HEIGHT;
    std::string title = DEFAULT_TITLE;
    bool fullscreen = DEFAULT_FULLSCREEN;

    // Try to load external config file
    if (std::filesystem::exists(CONFIG_FILE_PATH)) {
        try {
            std::ifstream file(CONFIG_FILE_PATH);
            json config;
            file >> config;

            // Parse window settings from JSON
            if (config.contains("window")) {
                const auto& window_config = config["window"];
                if (window_config.contains("width") && window_config["width"].is_number_integer()) {
                    width = window_config["width"].get<int>();
                    if (width <= 0) {
                        LOG_ERROR("Invalid width in config: must be positive");
                        return false;
                    }
                }
                if (window_config.contains("height") && window_config["height"].is_number_integer()) {
                    height = window_config["height"].get<int>();
                    if (height <= 0) {
                        LOG_ERROR("Invalid height in config: must be positive");
                        return false;
                    }
                }
                if (window_config.contains("title") && window_config["title"].is_string()) {
                    title = window_config["title"].get<std::string>();
                }
                if (window_config.contains("fullscreen") && window_config["fullscreen"].is_boolean()) {
                    fullscreen = window_config["fullscreen"].get<bool>();
                }
            }
        } catch (const std::exception& e) {
            LOG_ERROR("Error parsing config file {}: {}", CONFIG_FILE_PATH, e.what());
            // Continue with defaults instead of failing
        }
    }

    // Override with CLI arguments
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--fullscreen") {
            fullscreen = true;
        } else if (arg == "--width" && i + 1 < argc) {
            try {
                width = std::stoi(argv[++i]);
                if (width <= 0) throw std::invalid_argument("Width must be positive");
            } catch (const std::exception& e) {
                LOG_ERROR("Invalid width: {}", e.what());
                return false;
            }
        } else if (arg == "--height" && i + 1 < argc) {
            try {
                height = std::stoi(argv[++i]);
                if (height <= 0) throw std::invalid_argument("Height must be positive");
            } catch (const std::exception& e) {
                LOG_ERROR("Invalid height: {}", e.what());
                return false;
            }
        } else if (arg == "--title" && i + 1 < argc) {
            title = argv[++i];
        } else {
            LOG_ERROR("Usage: {} [--width W] [--height H] [--title T] [--fullscreen]", argv[0]);
            return false;
        }
    }

    return Init(width, height, title, fullscreen);
}

SDL_Window* Engine::GetWindow() const {
    if (!window) {
        LOG_ERROR("Attempted to access null window");
    }
    return window;
}

bool Initialize(int argc, char* argv[]) {
    LogInit();
    LOG_INFO("Genesis Engine Initializing...");

    if (g_Engine) {
        LOG_ERROR("Engine already initialized");
        return false;
    }

    g_Engine = new Engine();
    if (!g_Engine->InitFromArgs(argc, argv)) {
        delete g_Engine;
        g_Engine = nullptr;
        return false;
    }
    return true;
}

void Shutdown() {
    if (g_Engine) {
        LOG_INFO("Genesis Engine Shutting Down...");
        delete g_Engine;
        g_Engine = nullptr;
    }
    LOG_INFO("Genesis Engine Shutdown Complete");
}

} // namespace Engine