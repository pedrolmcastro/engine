#pragma once


#include "Precompiled.hpp"
#include "Debug/Color.hpp"

namespace Feather::Debug {
    class Log {
    public:
        enum class Level { TRACE, INFO, WARN, ERROR, FATAL, };
        static void SetPriority(Level level) { priority = level; }


        template<typename... Args> static void Print(Level level, Args&&... args) {
            if (priority > level) return;
            std::scoped_lock lock(mutex);

            std::underlying_type<Level>::type index = static_cast<std::underlying_type<Level>::type>(level);
            std::time_t timer = std::time(nullptr);
            std::tm* now = std::localtime(&timer);

            {
                Color color(colors[index].first, colors[index].second);
                std::cout << '[' << std::put_time(now, "%T") << "] " << bagdes[index] << ' ';
                (std::cout << ... << std::forward<Args>(args));
            }

            std::cout << std::endl;
        }
    private:
        inline static std::mutex mutex;
        inline static Level priority = Level::INFO;

        inline static const char* bagdes[] = { "TRACE:", "INFO: ", "WARN: ", "ERROR:", "FATAL:", };
        inline static const std::pair<Color::Foreground, Color::Background> colors[] {
            { Color::Foreground::WHITE,  Color::Background::NONE },
            { Color::Foreground::GREEN,  Color::Background::NONE },
            { Color::Foreground::YELLOW, Color::Background::NONE },
            { Color::Foreground::RED,    Color::Background::NONE },
            { Color::Foreground::WHITE,  Color::Background::RED  },
        };
    };
}


#ifdef LOGGING
    #define Trace(...) ::Feather::Debug::Log::Print(::Feather::Debug::Log::Level::TRACE __VA_OPT__(,) __VA_ARGS__)
    #define Info(...)  ::Feather::Debug::Log::Print(::Feather::Debug::Log::Level::INFO  __VA_OPT__(,) __VA_ARGS__)
    #define Warn(...)  ::Feather::Debug::Log::Print(::Feather::Debug::Log::Level::WARN  __VA_OPT__(,) __VA_ARGS__)
    #define Error(...) ::Feather::Debug::Log::Print(::Feather::Debug::Log::Level::ERROR __VA_OPT__(,) __VA_ARGS__)
    #define Fatal(...) ::Feather::Debug::Log::Print(::Feather::Debug::Log::Level::FATAL __VA_OPT__(,) __VA_ARGS__)
#else
    #define Trace(...)
    #define Info(...)
    #define Warn(...)
    #define Error(...)
    #define Fatal(...)
#endif
