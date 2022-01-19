#pragma once


#include "Precompiled.hpp"
#include "Debug/Color.hpp"

namespace Feather {
    class Log {
    public:
        enum class Level { TRACE, INFO, WARN, ERROR, FATAL };
        static void prioritize(Level level) { priority = level; }

        template<typename ...Args> static void trace(const char *message, Args... args) { log(Level::TRACE, message, args...); }
        template<typename ...Args> static void info(const char *message,  Args... args) { log(Level::INFO,  message, args...); }
        template<typename ...Args> static void warn(const char *message,  Args... args) { log(Level::WARN,  message, args...); }
        template<typename ...Args> static void error(const char *message, Args... args) { log(Level::ERROR, message, args...); }
        template<typename ...Args> static void fatal(const char *message, Args... args) { log(Level::FATAL, message, args...); }
    private:
        static std::mutex mtx;
        static Level priority;
        static const char *badges[];
        static std::pair<Color::Foreground, Color::Background> colors[];

        static void log(Level level, const char *message, ...);
    };
}
