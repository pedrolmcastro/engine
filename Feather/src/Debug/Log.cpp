#include "Precompiled.hpp"

#include "Debug/Log.hpp"
#include "Debug/Color.hpp"

using namespace std;
using namespace Feather;


mutex Debug::Log::mtx;
Debug::Log::Level Debug::Log::priority = Log::Level::INFO;
const char* Debug::Log::bagdes[] = { "TRACE:", "INFO: ", "WARN: ", "ERROR:", "FATAL:", };

pair<Debug::Color::Foreground, Debug::Color::Background> Debug::Log::colors[] = {
    { Color::Foreground::WHITE,  Color::Background::NONE },
    { Color::Foreground::GREEN,  Color::Background::NONE },
    { Color::Foreground::YELLOW, Color::Background::NONE },
    { Color::Foreground::RED,    Color::Background::NONE },
    { Color::Foreground::WHITE,  Color::Background::RED  },
};


// TODO: Use std::format()
void Debug::Log::Print(Level level, const char* message, ...) {
    if (priority <= level) {
        scoped_lock lock(mtx);

        time_t timer = time(nullptr);
        tm* now = localtime(&timer);

        {
            Color color(colors[int(level)].first, colors[int(level)].second);
            cout << '[' << put_time(now, "%T") << "] " << bagdes[int(level)] << ' ';

            va_list args;
            va_start(args, message);
            vprintf(message, args);
            va_end(args);
        }

        cout << endl;
    }
}
