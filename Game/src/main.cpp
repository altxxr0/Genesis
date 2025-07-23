// main.cpp
#include "Engine/Engine.h"
#include <SDL3/SDL.h>

int main(int argc, char* argv[]) {
    if (!Engine::Initialize(argc, argv)) {
        return 1;
    }

    // Main loop
    bool done = false;
    SDL_Event event;
    while (!done) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                done = true;
            }
        }
        SDL_Delay(10); // Prevent CPU overuse
    }

    Engine::Shutdown();
    return 0;
}