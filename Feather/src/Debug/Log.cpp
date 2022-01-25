#include "Precompiled.hpp"

#include "Debug/Log.hpp"
#include "Debug/Color.hpp"

using namespace std;
using namespace Feather;


mutex Log::mtx;
Log::Level Log::priority = Log::Level::INFO;
const char* Log::bagdes[] = { "TRACE", "INFO ", "WARN ", "ERROR", "FATAL", };

pair<Color::Foreground, Color::Background> Log::colors[] = {
    { Color::Foreground::WHITE,  Color::Background::NONE },
    { Color::Foreground::GREEN,  Color::Background::NONE },
    { Color::Foreground::YELLOW, Color::Background::NONE },
    { Color::Foreground::RED,    Color::Background::NONE },
    { Color::Foreground::WHITE,  Color::Background::RED  },
};


// TODO: Use std::format()
void Log::Print(Level level, const char* message, ...) {
    if (priority <= level) {
        scoped_lock lock(mtx);

        time_t timer = time(NULL);
        tm* now = localtime(&timer);

        {
            Color color(colors[int(level)].first, colors[int(level)].second);
            printf("[%02d:%02d:%02d %s] ", now->tm_hour, now->tm_min, now->tm_sec, bagdes[int(level)]);

            va_list args;
            va_start(args, message);
            vprintf(message, args);
            va_end(args);
        }

        cout << endl;
    }
}
