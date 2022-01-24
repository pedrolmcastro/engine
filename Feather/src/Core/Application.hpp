#pragma once


#include "Core/Memory.hpp"
#include "Core/Window.hpp"
#include "Input/Event.hpp"

namespace Feather {
    class Application {
    public:
        Application();
        virtual ~Application();

        // Defined by the client
        static Scope<Application> Create();

        void Run();
    private:
        Window window;
        bool running = true;

        void OnEvent(Event::Event& event);
        bool OnWindowClose(Event::WindowClose& event);
    };
}
