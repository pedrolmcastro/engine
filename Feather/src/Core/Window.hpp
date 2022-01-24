#pragma once


#include "Precompiled.hpp"

#include "Platform/GLFW/glfw3.h"
#include "Input/Event.hpp"

namespace Feather {
    class Window {
    public:
        Window(std::string name, unsigned width, unsigned height, bool vsync = true, std::function<void (Event::Event&)> callback = {});
        ~Window();

        void OnUpdate();

        bool IsVSync() const { return vsync; }
        void SetVSync(bool vsync);

        unsigned GetWidth() const { return width; }
        unsigned GetHeight() const { return height; }

        std::string GetName() const { return name; }
    private:
        static bool init;

        bool vsync;
        std::string name;
        GLFWwindow *window;
        unsigned width, height;
        std::function<void (Event::Event&)> callback;
    };
}
