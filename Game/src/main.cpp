#include "Engine/Engine.h"
#include "Engine/Log.h"

int main() {
    Engine::LogInit();

    LOG_INFO("Engine starting up...");
    LOG_DEBUG("This is a debug message.");
    LOG_WARN("This is a warning.");
    LOG_ERROR("This is an error!");

    Engine::Initialize();
    Engine::Shutdown();
    return 0;
}
