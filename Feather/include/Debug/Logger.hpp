#pragma once


#include <mutex>
#include <atomic>
#include <ostream>
#include <fstream>
#include <filesystem>

#include "Debug/Color.hpp"


namespace Feather::Debug {
    // From: https://youtu.be/-qAXShy1xiE
    template<class T> concept Printable = requires(std::ostream& output, T argument) { { output << argument } -> std::same_as<std::ostream&>; };

    class Logger {
    public:
        enum class Level { TRACE, INFO, WARN, ERROR, FATAL, NONE, };
        std::atomic<Level> priority;


        Logger(Level priority = Level::INFO, bool usecolor = true): priority(priority), usecolor(usecolor), output(std::clog) {}

        Logger(const std::filesystem::path& filepath, Level priority = Level::INFO, bool usecolor = false): priority(priority), usecolor(usecolor), output(file) {
            // TODO: Assets System
            std::filesystem::create_directories(filepath.parent_path());
            file.open(filepath);
        }


        void operator()(Level level, Printable auto ... arguments) const {
            #ifdef LOGGING
                if (priority > level) return;
                std::scoped_lock lock(mutex); // TODO: Use std::osyncstream

                if (usecolor) {
                    auto color = Color(output, colors[static_cast<std::underlying_type<Level>::type>(level)]);
                    Write(level, std::forward<decltype(arguments)>(arguments)...);
                }
                else {
                    Write(level, std::forward<decltype(arguments)>(arguments)...);
                }
            #endif
        }

        static Logger& Client() {
            static Logger client;
            return client;
        }

    private:
        std::ofstream file; // Own the ofstream if needed
        const bool usecolor;
        std::ostream& output;
        mutable std::mutex mutex;

        static constexpr const char* tags[] = { "Trace:", "Info: ", "Warn: ", "Error:", "Fatal:", };
        static constexpr Color::Code colors[] = { Color::Code::WHITE, Color::Code::GREEN, Color::Code::YELLOW, Color::Code::RED, Color::Code::RED, };


        void Write(Level level, Printable auto ... arguments) const {
            auto timer = std::time(nullptr);

            output << std::put_time(std::localtime(&timer), "%T") << ' ' << tags[static_cast<std::underlying_type<Level>::type>(level)] << ' ';
            (output << ... << std::forward<decltype(arguments)>(arguments)) << '\n';
        }

        static Logger& Core() {
            static Logger core("assets/logs/core.log", Level::TRACE);
            return core;
        }
    };
}


#define Trace(...) ::Feather::Debug::Logger::Client()(::Feather::Debug::Logger::Level::TRACE __VA_OPT__(,) __VA_ARGS__)
#define Info(...)  ::Feather::Debug::Logger::Client()(::Feather::Debug::Logger::Level::INFO  __VA_OPT__(,) __VA_ARGS__)
#define Warn(...)  ::Feather::Debug::Logger::Client()(::Feather::Debug::Logger::Level::WARN  __VA_OPT__(,) __VA_ARGS__)
#define Error(...) ::Feather::Debug::Logger::Client()(::Feather::Debug::Logger::Level::ERROR __VA_OPT__(,) __VA_ARGS__)
#define Fatal(...) ::Feather::Debug::Logger::Client()(::Feather::Debug::Logger::Level::FATAL __VA_OPT__(,) __VA_ARGS__)
