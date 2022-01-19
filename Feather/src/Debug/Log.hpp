#pragma once


#include "Precompiled.hpp"
#include "Debug/Color.hpp"

namespace Feather {
    class Log {
    public:
        enum class Level { TRACE, INFO, WARN, ERROR, FATAL };
        static void SetPriority(Level level) { priority = level; }

        template<typename ...Args> static void Trace(const char *message, Args... args) { Print(Level::TRACE, message, args...); }
        template<typename ...Args> static void Info(const char *message,  Args... args) { Print(Level::INFO,  message, args...); }
        template<typename ...Args> static void Warn(const char *message,  Args... args) { Print(Level::WARN,  message, args...); }
        template<typename ...Args> static void Error(const char *message, Args... args) { Print(Level::ERROR, message, args...); }
        template<typename ...Args> static void Fatal(const char *message, Args... args) { Print(Level::FATAL, message, args...); }
    private:
        static std::mutex mtx;
        static Level priority;
        static const char *badges[];
        static std::pair<Color::Foreground, Color::Background> colors[];

        static void Print(Level level, const char *message, ...);
    };
}
