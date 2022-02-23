#pragma once


#include "Precompiled.hpp"
#include "Math/Vector.hpp"

class GLFWwindow;

namespace Feather {
    class Input {
    public:
		enum class Key;
		enum class Mouse;

		static bool IsKeyPressed(Key key);
		static bool IsMousePressed(Mouse button);

		static Math::Double2 GetMousePosition();
		static double GetMouseX() { return GetMousePosition().x; }
		static double GetMouseY() { return GetMousePosition().y; }

        static void SetWindow(GLFWwindow* window_) { window = window_; }
    private:
        static GLFWwindow* window;
	};
}
