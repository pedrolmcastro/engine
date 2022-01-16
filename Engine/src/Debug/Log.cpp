#include "Precompiled.hpp"

#include "Log.hpp"

using namespace std;
using namespace Engine;


// Macro to print the formated message
#define print_formated      \
va_list args;               \
va_start(args, message);    \
vprintf(message, args);     \
va_end(args);               \
cout << endl;               \


// ANSI Console Colors
class Color {
public:
    enum class Foreground { RED = 91, GREEN = 92, YELLOW = 93, WHITE = 97};
    enum class Background { NONE = 0, RED = 101 };

    Color(Foreground fore, Background back = Background::NONE) {
        cout << "\e[0;" << (int)fore;
        if (back != Background::NONE) cout << ';' << (int)back;
        cout << 'm';
    }

    ~Color() {
        cout << "\e[0m\e[K";
    }
};


Log::Level Log::level = Log::Level::INFO;

void Log::set_level(Level level_) {
    level = level_;
}


void Log::trace(const char *message, ...) {
    if (level <= Level::TRACE) {
        Color color(Color::Foreground::WHITE);
        cout << "[Trace] ";
        print_formated;
    }
}

void Log::info(const char *message, ...) {
    if (level <= Level::INFO) {
        Color color(Color::Foreground::GREEN);
        cout << "[Info]  ";
        print_formated;
    }
}

void Log::warn(const char *message, ...) {
    if (level <= Level::WARN) {
        Color color(Color::Foreground::YELLOW);
        cout << "[Warn]  ";
        print_formated;
    }
}

void Log::error(const char *message, ...) {
    if (level <= Level::ERROR) {
        Color color(Color::Foreground::RED);
        cout << "[Error] ";
        print_formated;
    }
}

void Log::fatal(const char *message, ...) {
    if (level <= Level::FATAL) {
        Color color(Color::Foreground::WHITE, Color::Background::RED);
        cout << "[Fatal] ";
        print_formated;
    }
}
