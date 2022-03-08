#include "Input/Key.hpp"
#include "Input/Mouse.hpp"
#include "Input/Input.hpp"

#include "Math/Vector.hpp"

#include <GLFW/glfw3.h>

using namespace std;
using namespace Feather;


GLFWwindow* Input::window = nullptr;


bool Input::IsKeyPressed(Key key) {
    if (!window) return false;

    int state = glfwGetKey(window, static_cast<int>(key));
    return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool Input::IsMousePressed(Mouse button) {
    if (!window) return false;
    return glfwGetMouseButton(window, static_cast<int>(button)) == GLFW_PRESS;
}

Math::Double2 Input::GetMousePosition() {
    if (!window) return Math::Double2();

    double x, y;
    glfwGetCursorPos(window, &x, &y);
    return Math::Double2(x, y);
}
