#include "Precompiled.hpp"

#include "Debug/Assert.hpp"

#include "Render/Context.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;
using namespace Feather;


bool Render::Context::init = false;


Render::Context::Context() {
    if (!init) {
        bool success = glfwInit();
        __Assert__(success, "Failed to initialize GLFW!");

        glfwSetErrorCallback([](int error, const char* message) {
            stringstream stream;
            stream << "GLFW Error " << error << ": " << message;
            __Assert__(false, stream.str().c_str());
        });

        init = true;
    }
}

Render::Context::~Context() {
    glfwTerminate();
    init = false;
}

void Render::Context::Load(GLFWwindow* window) {
    glfwMakeContextCurrent(window);
    int success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	__Assert__(success, "Failed to initialize Glad!");
}
