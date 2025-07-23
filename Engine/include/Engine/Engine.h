// Engine.h
#pragma once
#include <SDL3/SDL.h>
#include <string>
#include <unordered_map>
#include <vector>

namespace Engine {

class Input {
public:
    Input();
    void Update(); // Process SDL3 events to update input state

    // Keyboard polling
    bool IsKeyDown(SDL_Scancode scancode) const;
    bool IsKeyPressed(SDL_Scancode scancode) const; // True only on press frame
    bool IsKeyReleased(SDL_Scancode scancode) const; // True only on release frame

    // Mouse polling
    bool IsMouseButtonDown(Uint32 button) const;
    bool IsMouseButtonPressed(Uint32 button) const;
    bool IsMouseButtonReleased(Uint32 button) const;
    void GetMousePosition(int& x, int& y) const;
    void GetMouseDelta(int& dx, int& dy) const;

    // Action-based input
    bool IsActionTriggered(const std::string& action) const;
    void LoadBindings(const std::string& config_file);

private:
    std::vector<bool> key_states; // Current state of keys
    std::vector<bool> key_pressed; // Keys pressed this frame
    std::vector<bool> key_released; // Keys released this frame
    std::vector<bool> mouse_states; // Current state of mouse buttons
    std::vector<bool> mouse_pressed; // Mouse buttons pressed this frame
    std::vector<bool> mouse_released; // Mouse buttons released this frame
    int mouse_x, mouse_y; // Current mouse position
    int mouse_dx, mouse_dy; // Mouse movement delta
    std::unordered_map<std::string, SDL_Scancode> action_bindings; // Action-to-key mappings
};

class Engine {
public:
    Engine();
    ~Engine();

    bool Init(int width, int height, const std::string& title, bool fullscreen = false);
    bool InitFromArgs(int argc, char* argv[]);
    SDL_Window* GetWindow() const;
    Input& GetInput();

private:
    SDL_Window* window;
    bool sdl_initialized;
    Input* m_Input;
};

bool Initialize(int argc, char* argv[]);
void Shutdown();

extern Engine* g_Engine;

} // namespace Engine