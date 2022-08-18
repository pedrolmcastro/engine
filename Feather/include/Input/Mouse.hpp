#pragma once


#include "Precompiled.hpp"
#include "Input/Input.hpp"

namespace Feather {
	// From GLFW 3
	enum class Input::Mouse {
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


    inline std::ostream& operator<<(std::ostream& stream, Input::Mouse button) { return stream << static_cast<std::underlying_type<Input::Mouse>::type>(button); }
}
