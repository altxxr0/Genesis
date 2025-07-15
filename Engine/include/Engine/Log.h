#pragma once
#include <string>

namespace Engine {

    enum class LogLevel {
        Info,
        Warning,
        Error,
        Debug
    };

    void LogInit(bool enableColor = true);
    void Log(LogLevel level, const std::string& message);

    #define LOG_INFO(msg)    ::Engine::Log(::Engine::LogLevel::Info, msg)
    #define LOG_WARN(msg)    ::Engine::Log(::Engine::LogLevel::Warning, msg)
    #define LOG_ERROR(msg)   ::Engine::Log(::Engine::LogLevel::Error, msg)
    #define LOG_DEBUG(msg)   ::Engine::Log(::Engine::LogLevel::Debug, msg)
} 
