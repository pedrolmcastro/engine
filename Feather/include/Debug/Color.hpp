#pragma once


#include "Precompiled.hpp"

namespace Feather::Debug {
    class Color {
    public:
        enum class Foreground { RED = 91, GREEN = 92, YELLOW = 93, WHITE = 97};
        enum class Background { NONE = 0, RED = 41 };


        Color(Foreground fore, Background back = Background::NONE) {
            std::cout << "\033[0;" << static_cast<std::underlying_type<Foreground>::type>(fore);
            if (back != Background::NONE) std::cout << ';' << static_cast<std::underlying_type<Background>::type>(back);
            std::cout << 'm';
        }

        ~Color() {
            std::cout << "\033[K\033[0m";
        }
    };
}
