#include "Precompiled.hpp"

#include "Debug/Assert.hpp"

#include "Render/Context.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;
using namespace Feather;


Render::Context::Context() {
    int success = glfwInit();
    __Assert__(success, "Failed to initialize GLFW!");

    glfwSetErrorCallback([](int error, const char* message) {
        // TODO: Use std::format()
        stringstream stream;
        stream << "GLFW Error " << error << ": " << message;
        __Assert__(false, stream.str().c_str());
    });
}

Render::Context::~Context() {
    glfwTerminate();
}

void Render::Context::Load(GLFWwindow* window) {
    glfwMakeContextCurrent(window);
    int success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	__Assert__(success, "Failed to initialize Glad!");
}
