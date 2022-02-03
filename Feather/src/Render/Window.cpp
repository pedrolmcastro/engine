#include "Precompiled.hpp"

#include "Debug/Assert.hpp"

#include "Input/Key.hpp"
#include "Input/Mouse.hpp"
#include "Input/Event.hpp"

#include "Render/Window.hpp"

#include "Platform/GLFW/glfw3.h"

using namespace std;
using namespace Feather;


Window::Window(string name, Math::Vector2 size, function<void (Event::Event&)> callback, bool vsync): name(name), size(size), callback(callback), vsync(vsync) {
    window = glfwCreateWindow(size.x, size.y, name.c_str(), nullptr, nullptr);
    __Assert__(window != nullptr, "Could not create the window!");

    glfwSetWindowUserPointer(window, this);
    glfwMakeContextCurrent(window);
    SetVSync(vsync);


    glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
		Window& self = *(Window*)glfwGetWindowUserPointer(window);
		self.size = { float(width), float(height) };

		Event::WindowResize event(self.size);
		if (self.callback) self.callback(event);
	});

    glfwSetCursorEnterCallback(window, [](GLFWwindow* window, int entered) {
        Window& self = *(Window*)glfwGetWindowUserPointer(window);

        if (entered) {
            Event::WindowEnter event;
            if (self.callback) self.callback(event);
        }
        else {
            Event::WindowLeave event;
            if (self.callback) self.callback(event);
        }
    });

	glfwSetWindowCloseCallback(window, [](GLFWwindow* window) {
		Window& self = *(Window*)glfwGetWindowUserPointer(window);

		Event::WindowClose event;
		if (self.callback) self.callback(event);
	});

    glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
        Window& self = *(Window*)glfwGetWindowUserPointer(window);

        switch (action) {
            case GLFW_PRESS: {
                Event::MousePress event((Mouse)button);
                if (self.callback) self.callback(event);
                break;
            }

            case GLFW_RELEASE: {
                Event::MouseRelease event((Mouse)button);
                if (self.callback) self.callback(event);
                break;
            }
        }
    });

    glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
        Window& self = *(Window*)glfwGetWindowUserPointer(window);

        Event::MouseScroll event({ float(xoffset), float(yoffset) });
        if (self.callback) self.callback(event);
    });

    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x, double y) {
        Window& self = *(Window*)glfwGetWindowUserPointer(window);

        Event::MouseMove event({ float(x), float(y) });
        if (self.callback) self.callback(event);
    });

	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		Window& self = *(Window*)glfwGetWindowUserPointer(window);

        switch (action) {
            case GLFW_PRESS: {
                Event::KeyPress event((Key)key, false);
                if (self.callback) self.callback(event);
                break;
            }

            case GLFW_REPEAT: {
                Event::KeyPress event((Key)key, true);
                if (self.callback) self.callback(event);
                break;
			}

            case GLFW_RELEASE: {
                Event::KeyRelease event((Key)key);
                if (self.callback) self.callback(event);
                break;
            }
		}
	});
}

Window::~Window() {
    glfwDestroyWindow(window);
}

void Window::OnUpdate() {
    glfwPollEvents();
    glfwSwapBuffers(window);
}

void Window::SetVSync(bool vsync) {
    glfwSwapInterval(vsync);
    this->vsync = vsync;
}
