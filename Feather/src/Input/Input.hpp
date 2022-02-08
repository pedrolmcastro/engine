#pragma once


#include "Precompiled.hpp"

#include "Input/Key.hpp"
#include "Input/Mouse.hpp"
#include "Math/Vector.hpp"

class GLFWwindow;

namespace Feather {
    class Input {
    public:
		static bool IsKeyPressed(Key key);
		static bool IsMousePressed(Mouse button);

		static Math::Vector2 GetMousePosition();
		static float GetMouseX() { return GetMousePosition().x; }
		static float GetMouseY() { return GetMousePosition().y; }

        static void SetWindow(GLFWwindow* window_) { window = window_; }
    private:
        static GLFWwindow* window;
	};
}
