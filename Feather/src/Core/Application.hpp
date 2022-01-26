#pragma once


#include "Core/Layer.hpp"
#include "Core/Memory.hpp"
#include "Core/Window.hpp"
#include "Input/Event.hpp"

namespace Feather {
    class Application {
    public:
        Application();
        virtual ~Application();

        // Defined by the client
        static Unique<Application> Create();

        void Run();
    protected:
        void Push(Unique<Layer::Layer> layer) { layers.Push(std::move(layer)); }
        Unique<Layer::Layer> Pop() { return layers.Pop(); }
    private:
        Window window;
        Layer::Stack layers;
        bool running = true;

        void OnEvent(Event::Event& event);
        bool OnWindowClose(Event::WindowClose& event);
    };
}
