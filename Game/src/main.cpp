#include "Engine/Engine.h"
#include "Engine/Log.h"
#include "Platform/SDLWindow.h"

int main() {
    Engine::LogInit();
    LOG_INFO("Genesis Game Starting...");

    Engine::SDLWindow window("Genesis Engine", 1280, 720);

    while (!window.ShouldClose()) {
        window.PollEvents();
    }

    return 0;
}
