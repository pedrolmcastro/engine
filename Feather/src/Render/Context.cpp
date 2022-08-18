#include "Precompiled.hpp"

#include "Debug/Assert.hpp"

#include "Render/Context.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;
using namespace Feather;


Render::Context::Context() {
    int success = glfwInit();
    Assert(success, "Failed to initialize GLFW!");
    Unused(success);

    glfwSetErrorCallback([](int error, const char* message) {
        Assert(false, "GLFW Error ", error, ": ", message);
    });
}

Render::Context::~Context() {
    glfwTerminate();
}


void Render::Context::Version() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Render::Context::Load(GLFWwindow* window) {
    glfwMakeContextCurrent(window);

    int success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	Assert(success, "Failed to initialize Glad!");
    Unused(success);


    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);

    glDebugMessageCallback([](unsigned source, unsigned type, unsigned id, unsigned severity, int length, const char* message, const void* parameter) {
        switch (severity) {
			case GL_DEBUG_SEVERITY_NOTIFICATION: Trace(message); break;
			case GL_DEBUG_SEVERITY_LOW:          Warn(message);  break;
			case GL_DEBUG_SEVERITY_MEDIUM:       Error(message); break;
			case GL_DEBUG_SEVERITY_HIGH:         Fatal(message); break;
		}
    }, nullptr);

    glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
