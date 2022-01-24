#pragma once


#include "Precompiled.hpp"

#include "Platform/GLFW/glfw3.h"
#include "Input/Mouse.hpp"
#include "Input/Key.hpp"

namespace Feather {
    class Input {
    public:
		static bool IsKeyPressed(Key key);
		static bool IsMousePressed(Mouse button);

        // TODO: Use Float2
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX() { return GetMousePosition().first; }
		static float GetMouseY() { return GetMousePosition().second; }

        static void SetWindow(GLFWwindow* window_) { window = window_; }
    private:
        static GLFWwindow* window;
	};
}
