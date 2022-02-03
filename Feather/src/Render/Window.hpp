#pragma once


#include "Precompiled.hpp"
#include "Input/Event.hpp"
#include "Math/Vector.hpp"
#include "Platform/GLFW/glfw3.h"

namespace Feather {
    class Window {
    public:
        Window(std::string name, Math::Vector2 size, std::function<void (Event::Event&)> callback = {}, bool vsync = true);
        ~Window();

        void OnUpdate();

        bool IsVSync() const { return vsync; }
        void SetVSync(bool vsync);

        float GetWidth() const { return size.x; }
        float GetHeight() const { return size.y; }
        Math::Vector2 GetSize() const { return size; }

        operator std::string() const { return name; }
        operator GLFWwindow*() const { return window; }
    private:
        bool vsync;
        std::string name;
        Math::Vector2 size;
        GLFWwindow* window;
        std::function<void (Event::Event&)> callback;
    };
}
