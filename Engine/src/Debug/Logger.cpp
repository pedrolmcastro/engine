#include "Precompiled.hpp"

#include "Color.hpp"
#include "Logger.hpp"

using namespace std;
using namespace Engine;


mutex Logger::mtx;
Logger::Level Logger::priority = Logger::Level::INFO;

const char *Logger::badges[] = {
    "[Trace] ",
    "[Info]  ",
    "[Warn]  ",
    "[Error] ",
    "[Fatal] ",
};

pair<Color::Foreground, Color::Background> Logger::colors[] = {
    { Color::Foreground::WHITE,  Color::Background::NONE },
    { Color::Foreground::GREEN,  Color::Background::NONE },
    { Color::Foreground::YELLOW, Color::Background::NONE },
    { Color::Foreground::RED,    Color::Background::NONE },
    { Color::Foreground::WHITE,  Color::Background::RED  },
};


void Logger::log(Level level, const char *message, ...) {
    if (priority <= level) {
        // Thread Safety
        scoped_lock lock(mtx);

        Color color(colors[int(level)].first, colors[int(level)].second);
        cout << badges[int(level)];

        // Print the Formated Message
        va_list args;
        va_start(args, message);
        vprintf(message, args);
        va_end(args);

        cout << endl;
    }
}
