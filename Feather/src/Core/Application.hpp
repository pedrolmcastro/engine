#pragma once


#include "Precompiled.hpp"

#include "Core/Event.hpp"
#include "Core/Layer.hpp"
#include "Core/Memory.hpp"
#include "Render/Window.hpp"
#include "Render/Context.hpp"
// Temporary
#include "Render/Index.hpp"
#include "Render/Vertex.hpp"
#include "Render/Shader.hpp"

namespace Feather {
    class Application {
    public:
        Application(const std::string& name, Math::Vector2 size, bool vsync = true);
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
        // Temporary
        Render::Vertex::Array vertexarray;
        Render::Shader shader = { "assets/shaders/Default.glsl" };

        void OnEvent(Event::Event& event);
        bool OnWindowClose(Event::WindowClose& event);
    };
}
