#pragma once


#include "Precompiled.hpp"

namespace Feather {
	// From GLFW 3
	enum class Mouse {
        B0     = 0,
        B1     = 1,
        B2     = 2,
        B3     = 3,
        B4     = 4,
        B5     = 5,
        B6     = 6,
        B7     = 7,

        LEFT   = B0,
        RIGHT  = B1,
        MIDDLE = B2,
	};

    inline std::ostream& operator<<(std::ostream& stream, Mouse button) { stream << int(button); return stream; }
}
