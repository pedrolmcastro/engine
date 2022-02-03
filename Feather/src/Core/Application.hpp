#pragma once


#include "Precompiled.hpp"

#include "Core/Event.hpp"
#include "Core/Layer.hpp"
#include "Core/Memory.hpp"
#include "Math/Vector.hpp"
#include "Render/Window.hpp"
#include "Render/Context.hpp"

namespace Feather {
    class Application {
    public:
        Application(std::string name, Math::Vector2 size, bool vsync = true);
        virtual ~Application();

        // Defined by the client
        static Unique<Application> Create();

        void Run();
    private:
        Render::Context context; // Must be constructed before the window
        bool running = true;

        void OnEvent(Event::Event& event);
        bool OnWindowClose(Event::WindowClose& event);
    protected:
        Layer::Stack layers;
        Window window;
    };
}
