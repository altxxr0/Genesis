// main.cpp
#include "Engine/Engine.h"
#include <SDL3/SDL.h>
#include <Engine/Log.h>

int main(int argc, char* argv[]) {
    if (!Engine::Initialize(argc, argv)) {
        return 1;
    }

    Engine::Input& input = Engine::g_Engine->GetInput();
    bool done = false;

    while (!done) {
        input.Update();
        if (input.IsActionTriggered("quit") || input.IsKeyPressed(SDL_SCANCODE_ESCAPE)) {
            done = true;
        }
        if (input.IsMouseButtonPressed(SDL_BUTTON_LEFT)) {
            int x, y;
            input.GetMousePosition(x, y);
            LOG_INFO("Mouse clicked at ({}, {})", x, y);
        }
        if (input.IsActionTriggered("jump")) {
            LOG_INFO("Jump action triggered!");
        }
        SDL_Delay(10);
    }

    Engine::Shutdown();
    return 0;
}