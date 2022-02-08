#pragma once


#include "Precompiled.hpp"
#include "Math/Vector.hpp"
#include "Core/Event.hpp"

class GLFWwindow;

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

        bool IsFocused() const;
        bool IsHovered() const;
        bool IsMinimized() const;
        bool IsMaximized() const;

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
