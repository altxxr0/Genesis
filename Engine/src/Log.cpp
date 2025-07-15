#include "Engine/Log.h"
#include <iostream>
#include <mutex>

#ifdef _WIN32
#include <windows.h>
#endif

namespace Engine {

    static bool s_EnableColor = true;
    static std::mutex s_LogMutex;

    void LogInit(bool enableColor) {
        s_EnableColor = enableColor;

#ifdef _WIN32
        if (s_EnableColor) {
            HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
            if (hOut != INVALID_HANDLE_VALUE) {
                DWORD dwMode = 0;
                GetConsoleMode(hOut, &dwMode);
                SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
            }
        }
#endif
    }

    void Log(LogLevel level, const std::string& message) {
        std::lock_guard<std::mutex> lock(s_LogMutex);

        std::string prefix;
        std::string color;

        switch (level) {
            case LogLevel::Info:
                prefix = "[INFO] ";
                color = "\033[1;37m";
                break;
            case LogLevel::Warning:
                prefix = "[WARN] ";
                color = "\033[1;33m";
                break;
            case LogLevel::Error:
                prefix = "[ERROR]";
                color = "\033[1;31m";
                break;
            case LogLevel::Debug:
                prefix = "[DEBUG]";
                color = "\033[1;36m";
                break;
        }

        if (s_EnableColor)
            std::cout << color;

        std::cout << prefix << " " << message;

        if (s_EnableColor)
            std::cout << "\033[0m";

        std::cout << std::endl;
    }

}
