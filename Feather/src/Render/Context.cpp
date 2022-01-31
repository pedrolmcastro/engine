#include "Debug/Assert.hpp"

#include "Render/Context.hpp"

#include "Platform/GLFW/glfw3.h"

using namespace std;
using namespace Feather;


bool Render::Context::init = false;


Render::Context::Context() {
    if (!init) {
        bool success = glfwInit();
        __Assert__(success, "Could not initialize GLFW!");

        // TODO: Add Glad
    }

    init = true;
}

Render::Context::~Context() {
    glfwTerminate();
    init = false;
}
