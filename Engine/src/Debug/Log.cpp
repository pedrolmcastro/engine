#include "Precompiled.hpp"

#include "Log.hpp"
#include "Color.hpp"

using namespace std;
using namespace Engine;


mutex Log::mtx;

#ifdef DEBUG
    Log::Level Log::priority = Log::Level::TRACE;
#else
    Log::Level Log::priority = Log::Level::INFO;
#endif

const char *Log::badges[] = {
    "[Trace] ",
    "[Info]  ",
    "[Warn]  ",
    "[Error] ",
    "[Fatal] ",
};

pair<Color::Foreground, Color::Background> Log::colors[] = {
    { Color::Foreground::WHITE,  Color::Background::NONE },
    { Color::Foreground::GREEN,  Color::Background::NONE },
    { Color::Foreground::YELLOW, Color::Background::NONE },
    { Color::Foreground::RED,    Color::Background::NONE },
    { Color::Foreground::WHITE,  Color::Background::RED  },
};


void Log::log(Level level, const char *message, ...) {
    if (priority <= level) {
        // Thread Safety
        scoped_lock lock(mtx);

        {
            Color color(colors[int(level)].first, colors[int(level)].second);
            cout << badges[int(level)];

            // Print the Formated Message
            va_list args;
            va_start(args, message);
            vprintf(message, args);
            va_end(args);
        }

        cout << endl;
    }
}
