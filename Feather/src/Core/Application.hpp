#pragma once


#include "Precompiled.hpp"

#include "Core/Event.hpp"
#include "Core/Layer.hpp"
#include "Core/Memory.hpp"
#include "Render/Window.hpp"
#include "Render/Context.hpp"

namespace Feather {
    class Application {
    public:
        Application(const std::string& title, Math::Unsigned2 size, bool vsync = true);
        virtual ~Application() = default;

        // Defined by the client
        static Unique<Application> Create();

        void Run();
        void Close() { running = false; }
    protected:
        Render::Context context; // Constructed before window
        Render::Window window;
        Layer::Stack layers;
    private:
        bool running = true;
        std::chrono::high_resolution_clock clock;
        std::chrono::high_resolution_clock::time_point last = clock.now();

        void OnEvent(Event& event);
        bool OnWindowClose(Event::WindowClose& event);
        bool OnWindowResize(Event::WindowResize& event);
    };
}
