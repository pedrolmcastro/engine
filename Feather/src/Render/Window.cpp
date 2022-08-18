#include "Precompiled.hpp"

#include "Core/Event.hpp"
#include "Core/Application.hpp"

#include "Debug/Assert.hpp"

#include "Input/Key.hpp"
#include "Input/Input.hpp"
#include "Input/Mouse.hpp"

#include "Math/Vector.hpp"

#include "Render/Window.hpp"
#include "Render/Command.hpp"
#include "Render/Context.hpp"

#include <GLFW/glfw3.h>

using namespace std;
using namespace Feather;


Render::Window::Window(const string& title, const Math::Unsigned2& size, bool vsync): vsync(vsync), title(title), size(size) {
    Render::Context::Version();

    window = glfwCreateWindow(size.x, size.y, title.c_str(), nullptr, nullptr);
    Assert(window, "Failed to create window!");

    glfwSetWindowUserPointer(window, this);
    Input::SetWindow(window);
    Context::Load(window);
    SetVSync(vsync);


    glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
		Window& self = *(Window*)glfwGetWindowUserPointer(window);
		self.size = Math::Unsigned2(width, height);

        Render::Command::SetViewport(0, 0, width, height);
		Event::WindowResize event(self.size);
		Application::Dispatch(event);
	});

    glfwSetWindowIconifyCallback(window, [](GLFWwindow* window, int minimized) {
        Window& self = *(Window*)glfwGetWindowUserPointer(window);

        if (minimized) {
            self.size = Math::Unsigned2();

            Event::WindowResize event(self.size);
            Application::Dispatch(event);
        }
        else {
            int width, height;
            glfwGetWindowSize(window, &width, &height);
            self.size = Math::Unsigned2(width, height);

            Event::WindowResize event(self.size);
            Application::Dispatch(event);
        }
    });

    glfwSetWindowPosCallback(window, [](GLFWwindow* window, int x, int y) {
        Window& self = *(Window*)glfwGetWindowUserPointer(window);
        self.position = Math::Int2(x, y);

        Event::WindowMove event(self.position);
        Application::Dispatch(event);
    });

    glfwSetWindowFocusCallback(window, [](GLFWwindow* window, int focused) {
        if (focused) {
            Event::WindowFocus event;
            Application::Dispatch(event);
        }
        else {
            Event::WindowUnfocus event;
            Application::Dispatch(event);
        }
    });

    glfwSetCursorEnterCallback(window, [](GLFWwindow* window, int hovered) {
        if (hovered) {
            Event::WindowHover event;
            Application::Dispatch(event);
        }
        else {
            Event::WindowUnhover event;
            Application::Dispatch(event);
        }
    });

	glfwSetWindowCloseCallback(window, [](GLFWwindow* window) {
		Event::WindowClose event;
		Application::Dispatch(event);
	});

    glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int modifiers) {
        switch (action) {
            case GLFW_PRESS: {
                Event::MousePress event(static_cast<Input::Mouse>(button));
                Application::Dispatch(event);
                break;
            }

            case GLFW_RELEASE: {
                Event::MouseRelease event(static_cast<Input::Mouse>(button));
                Application::Dispatch(event);
                break;
            }
        }
    });

    glfwSetScrollCallback(window, [](GLFWwindow* window, double x, double y) {
        Event::MouseScroll event(Math::Double2(x, y));
        Application::Dispatch(event);
    });

    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x, double y) {
        Event::MouseMove event(Math::Double2(x, y));
        Application::Dispatch(event);
    });

	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int modifiers) {
        switch (action) {
            case GLFW_PRESS: {
                Event::KeyPress event(static_cast<Input::Key>(key), false);
                Application::Dispatch(event);
                break;
            }

            case GLFW_REPEAT: {
                Event::KeyPress event(static_cast<Input::Key>(key), true);
                Application::Dispatch(event);
                break;
			}

            case GLFW_RELEASE: {
                Event::KeyRelease event(static_cast<Input::Key>(key));
                Application::Dispatch(event);
                break;
            }
		}
	});
}

Render::Window::~Window() {
    glfwDestroyWindow(window);
}


void Render::Window::OnUpdate() const {
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
