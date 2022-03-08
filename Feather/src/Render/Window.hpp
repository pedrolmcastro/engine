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
        Window(const std::string& title, const Math::Unsigned2& size, std::function<void (Event&)> callback = {}, bool vsync = true);
        ~Window();


        void OnUpdate() const;

        bool IsVSync() const { return vsync; }
        void SetVSync(bool vsync);

        bool IsFocused() const;
        bool IsHovered() const;
        bool IsMinimized() const;
        bool IsMaximized() const;


        unsigned GetWidth() const { return size.x; }
        unsigned GetHeight() const { return size.y; }
        Math::Unsigned2 GetSize() const { return size; }

        int GetX() const { return position.x; }
        int GetY() const { return position.y; }
        Math::Int2 GetPosition() const { return position; }

        std::string GetTitle() const { return title; }


        operator GLFWwindow*() const { return window; }
    private:
        bool vsync;
        std::string title;
        GLFWwindow* window;
        Math::Int2 position;
        Math::Unsigned2 size;
        std::function<void (Event&)> callback;
    };
}
