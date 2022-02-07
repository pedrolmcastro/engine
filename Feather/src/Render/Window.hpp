#pragma once


#include "Precompiled.hpp"

#include "Core/Event.hpp"
#include "Math/Vector.hpp"

// TODO: Use Forward Declaration
#include <GLFW/glfw3.h>

// TODO: Add Icon
// TODO: Add Maximized Constructor
namespace Feather::Render {
    class Window {
    public:
        Window(std::string name, const Math::Vector2& size, std::function<void (Event::Event&)> callback = {}, bool vsync = true);
        ~Window();

        void OnUpdate();

        bool IsVSync() const { return vsync; }
        void SetVSync(bool vsync);

        bool IsFocused() const { return glfwGetWindowAttrib(window, GLFW_FOCUSED); }
        bool IsHovered() const { return glfwGetWindowAttrib(window, GLFW_HOVERED); }
        
        bool IsMinimized() const { return size.x == 0.0f || size.y == 0.0f; }
        bool IsMaximized() const { return glfwGetWindowAttrib(window, GLFW_MAXIMIZED); }
        
        float GetWidth() const { return size.x; }
        float GetHeight() const { return size.y; }
        Math::Vector2 GetSize() const { return size; }

        float GetX() const { return position.x; }
        float GetY() const { return position.y; }
        Math::Vector2 GetPosition() const { return position; }

        operator std::string() const { return name; }
        operator GLFWwindow*() const { return window; }
    private:
        bool vsync;
        std::string name;
        GLFWwindow* window;
        Math::Vector2 size, position;
        std::function<void (Event::Event&)> callback;
    };
}
