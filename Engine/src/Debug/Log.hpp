#pragma once


namespace Engine {
    class Log {
    public:
        enum class Level { TRACE, INFO, WARN, ERROR, FATAL };
        static void set_level(Level level_);

        static void trace(const char *message, ...);
        static void info(const char *message, ...);
        static void warn(const char *message, ...);
        static void error(const char *message, ...);
        static void fatal(const char *message, ...);
    private:
        static Level level;
    };
}
