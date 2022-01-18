#pragma once


namespace Feather {
    class Color {
    public:
        enum class Foreground { RED = 91, GREEN = 92, YELLOW = 93, WHITE = 97};
        enum class Background { NONE = 0, RED = 41 };

        Color(Foreground fore, Background back = Background::NONE);
        ~Color();
    };
}
