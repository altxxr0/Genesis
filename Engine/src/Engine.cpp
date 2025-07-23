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

// Input class implementation
Input::Input() {
    key_states.resize(SDL_SCANCODE_COUNT, false);
    key_pressed.resize(SDL_SCANCODE_COUNT, false);
    key_released.resize(SDL_SCANCODE_COUNT, false);
    mouse_states.resize(SDL_BUTTON_X2 + 1, false);
    mouse_pressed.resize(SDL_BUTTON_X2 + 1, false);
    mouse_released.resize(SDL_BUTTON_X2 + 1, false);
    mouse_x = mouse_y = 0;
    mouse_dx = mouse_dy = 0;

    action_bindings["jump"] = SDL_SCANCODE_SPACE;
    action_bindings["quit"] = SDL_SCANCODE_ESCAPE;
}

void Input::Update() {
    std::fill(key_pressed.begin(), key_pressed.end(), false);
    std::fill(key_released.begin(), key_released.end(), false);
    std::fill(mouse_pressed.begin(), mouse_pressed.end(), false);
    std::fill(mouse_released.begin(), mouse_released.end(), false);
    mouse_dx = mouse_dy = 0;

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_KEY_DOWN:
                key_states[event.key.scancode] = true;
                key_pressed[event.key.scancode] = true;
                break;
            case SDL_EVENT_KEY_UP:
                key_states[event.key.scancode] = false;
                key_released[event.key.scancode] = true;
                break;
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                mouse_states[event.button.button] = true;
                mouse_pressed[event.button.button] = true;
                break;
            case SDL_EVENT_MOUSE_BUTTON_UP:
                mouse_states[event.button.button] = false;
                mouse_released[event.button.button] = true;
                break;
            case SDL_EVENT_MOUSE_MOTION:
                mouse_x = event.motion.x;
                mouse_y = event.motion.y;
                mouse_dx = event.motion.xrel;
                mouse_dy = event.motion.yrel;
                break;
        }
    }
}

bool Input::IsKeyDown(SDL_Scancode scancode) const {
    return scancode < key_states.size() ? key_states[scancode] : false;
}

bool Input::IsKeyPressed(SDL_Scancode scancode) const {
    return scancode < key_pressed.size() ? key_pressed[scancode] : false;
}

bool Input::IsKeyReleased(SDL_Scancode scancode) const {
    return scancode < key_released.size() ? key_released[scancode] : false;
}

bool Input::IsMouseButtonDown(Uint32 button) const {
    return button < mouse_states.size() ? mouse_states[button] : false;
}

bool Input::IsMouseButtonPressed(Uint32 button) const {
    return button < mouse_pressed.size() ? mouse_pressed[button] : false;
}

bool Input::IsMouseButtonReleased(Uint32 button) const {
    return button < mouse_released.size() ? mouse_released[button] : false;
}

void Input::GetMousePosition(int& x, int& y) const {
    x = mouse_x;
    y = mouse_y;
}

void Input::GetMouseDelta(int& dx, int& dy) const {
    dx = mouse_dx;
    dy = mouse_dy;
}

bool Input::IsActionTriggered(const std::string& action) const {
    auto it = action_bindings.find(action);
    if (it != action_bindings.end()) {
        return IsKeyPressed(it->second);
    }
    return false;
}

void Input::LoadBindings(const std::string& config_file) {
    if (!std::filesystem::exists(config_file)) {
        LOG_INFO("No config file for input bindings at {}, using defaults", config_file);
        return;
    }

    try {
        std::ifstream file(config_file);
        json config;
        file >> config;

        if (config.contains("input") && config["input"].contains("bindings")) {
            for (const auto& [action, key] : config["input"]["bindings"].items()) {
                if (key.is_string()) {
                    std::string key_str = key.get<std::string>();
                    SDL_Scancode scancode = SDL_GetScancodeFromName(key_str.c_str());
                    if (scancode != SDL_SCANCODE_UNKNOWN) {
                        action_bindings[action] = scancode;
                    } else {
                        LOG_ERROR("Invalid scancode in config: {}", key_str);
                    }
                }
            }
        }
    } catch (const std::exception& e) {
        LOG_ERROR("Error parsing input bindings from {}: {}", config_file, e.what());
    }
}

Engine::Engine() : window(nullptr) {
        m_Input = new Input();
    }

Engine::~Engine() {
    delete m_Input;
    if (window) {
        SDL_DestroyWindow(window);
    }
    if (sdl_initialized) {
        SDL_Quit();
    }
}

Input& Engine::GetInput() {
        return *m_Input;
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