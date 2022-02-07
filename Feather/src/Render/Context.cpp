#include "Precompiled.hpp"

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

        glfwSetErrorCallback([](int error, const char* message) {
            stringstream stream;
            stream << "GLFW Error " << error << ": " << message;
            __Assert__(false, stream.str().c_str());
        });

        // TODO: Add Glad
    }

    init = true;
}

Render::Context::~Context() {
    glfwTerminate();
    init = false;
}
