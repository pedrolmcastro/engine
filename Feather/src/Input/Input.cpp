#include "Input/Key.hpp"
#include "Input/Mouse.hpp"
#include "Input/Input.hpp"

#include "Platform/GLFW/glfw3.h"

using namespace std;
using namespace Feather;


GLFWwindow* Input::window = nullptr;


bool Input::IsKeyPressed(Key key) {
    if (window == nullptr) return false;

    int state = glfwGetKey(window, int(key));
    return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool Input::IsMousePressed(Mouse button) {
    if (window == nullptr) return false;
    return glfwGetMouseButton(window, int(button)) == GLFW_PRESS;
}

pair<float, float> Input::GetMousePosition() {
    if (window == nullptr) return { 0, 0 };

    double x, y;
    glfwGetCursorPos(window, &x, &y);
    return { x, y };
}
