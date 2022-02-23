#include "Precompiled.hpp"

#include "Core/Event.hpp"

#include "Debug/Assert.hpp"

#include "Input/Key.hpp"
#include "Input/Mouse.hpp"

#include "Math/Vector.hpp"

#include "Render/Window.hpp"
#include "Render/Context.hpp"

#include <GLFW/glfw3.h>

using namespace std;
using namespace Feather;


Render::Window::Window(const string& title, const Math::Unsigned2& size, function<void (Event&)> callback, bool vsync): title(title), size(size), callback(callback), vsync(vsync) {
    window = glfwCreateWindow(size.x, size.y, title.c_str(), nullptr, nullptr);
    Assert(window != nullptr, "Failed to create window!");

    glfwSetWindowUserPointer(window, this);
    Context::Load(window);
    SetVSync(vsync);


    glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
		Window& self = *(Window*)glfwGetWindowUserPointer(window);
		self.size = { unsigned(width), unsigned(height) };

		Event::WindowResize event(self.size);
		if (self.callback) self.callback(event);
	});

    glfwSetWindowIconifyCallback(window, [](GLFWwindow* window, int minimized) {
        Window& self = *(Window*)glfwGetWindowUserPointer(window);

        if (minimized) {
            self.size = { 0, 0 };

            Event::WindowResize event(self.size);
            if (self.callback) self.callback(event);
        }
        else {
            int width, height;
            glfwGetWindowSize(window, &width, &height);
            self.size = { unsigned(width), unsigned(height) };

            Event::WindowResize event(self.size);
            if (self.callback) self.callback(event);
        }
    });

    glfwSetWindowPosCallback(window, [](GLFWwindow* window, int x, int y) {
        Window& self = *(Window*)glfwGetWindowUserPointer(window);
        self.position = { x, y };

        Event::WindowMove event(self.position);
        if (self.callback) self.callback(event);
    });

    glfwSetWindowFocusCallback(window, [](GLFWwindow* window, int focused) {
        Window& self = *(Window*)glfwGetWindowUserPointer(window);

        if (focused) {
            Event::WindowFocus event;
            if (self.callback) self.callback(event);
        }
        else {
            Event::WindowUnfocus event;
            if (self.callback) self.callback(event);
        }
    });

    glfwSetCursorEnterCallback(window, [](GLFWwindow* window, int hovered) {
        Window& self = *(Window*)glfwGetWindowUserPointer(window);

        if (hovered) {
            Event::WindowHover event;
            if (self.callback) self.callback(event);
        }
        else {
            Event::WindowUnhover event;
            if (self.callback) self.callback(event);
        }
    });

	glfwSetWindowCloseCallback(window, [](GLFWwindow* window) {
		Window& self = *(Window*)glfwGetWindowUserPointer(window);

		Event::WindowClose event;
		if (self.callback) self.callback(event);
	});

    glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int modifiers) {
        Window& self = *(Window*)glfwGetWindowUserPointer(window);

        switch (action) {
            case GLFW_PRESS: {
                Event::MousePress event((Input::Mouse)button);
                if (self.callback) self.callback(event);
                break;
            }

            case GLFW_RELEASE: {
                Event::MouseRelease event((Input::Mouse)button);
                if (self.callback) self.callback(event);
                break;
            }
        }
    });

    glfwSetScrollCallback(window, [](GLFWwindow* window, double x, double y) {
        Window& self = *(Window*)glfwGetWindowUserPointer(window);

        Event::MouseScroll event({ x, y });
        if (self.callback) self.callback(event);
    });

    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x, double y) {
        Window& self = *(Window*)glfwGetWindowUserPointer(window);

        Event::MouseMove event({ x, y });
        if (self.callback) self.callback(event);
    });

	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int modifiers) {
		Window& self = *(Window*)glfwGetWindowUserPointer(window);

        switch (action) {
            case GLFW_PRESS: {
                Event::KeyPress event((Input::Key)key, false);
                if (self.callback) self.callback(event);
                break;
            }

            case GLFW_REPEAT: {
                Event::KeyPress event((Input::Key)key, true);
                if (self.callback) self.callback(event);
                break;
			}

            case GLFW_RELEASE: {
                Event::KeyRelease event((Input::Key)key);
                if (self.callback) self.callback(event);
                break;
            }
		}
	});
}

Render::Window::~Window() {
    glfwDestroyWindow(window);
}

void Render::Window::OnUpdate() {
    glfwPollEvents();
    glfwSwapBuffers(window);
}

void Render::Window::SetVSync(bool vsync) {
    glfwMakeContextCurrent(window);
    glfwSwapInterval(vsync);
    this->vsync = vsync;
}

bool Render::Window::IsFocused() const {
    return glfwGetWindowAttrib(window, GLFW_FOCUSED);
}

bool Render::Window::IsHovered() const {
    return glfwGetWindowAttrib(window, GLFW_HOVERED);
}

bool Render::Window::IsMinimized() const {
    return size.x == 0 || size.y == 0;
}

bool Render::Window::IsMaximized() const {
    return glfwGetWindowAttrib(window, GLFW_MAXIMIZED);
}
