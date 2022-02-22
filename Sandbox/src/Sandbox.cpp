#include "Feather.hpp"

using namespace std;
using namespace Feather;


class Runtime: public Layer {
public:
    void OnAttach() override {
        Render::Vertex::Layout layout = {
            { Render::Shader::Data::VECTOR3 }, // a_Position
            { Render::Shader::Data::VECTOR4 }, // a_Color
        };

        float vertices[3 * (3 + 4)] = {
            -0.5f, -0.5f, 0.0f,  0.8f, 0.2f, 0.2f, 1.0f,
             0.5f, -0.5f, 0.0f,  0.2f, 0.8f, 0.2f, 1.0f,
             0.0f,  0.5f, 0.0f,  0.2f, 0.2f, 0.8f, 1.0f,
        };

        unsigned indices[3] = { 0, 1, 2 };

        vertexarray.AddVertex(Shared<Render::Vertex::Buffer>(layout, sizeof(vertices), vertices));
        vertexarray.SetIndex(Shared<Render::Index::Buffer>(sizeof(indices), indices));
    }

    void OnUpdate(Time delta) override {
        shader.Bind();
        vertexarray.Bind();

        Render::Command::Draw(vertexarray);
    }

    void OnEvent(Event& event) override {
        Event::Dispatcher dispatcher(event);
    }
private:
    Render::Vertex::Array vertexarray;
    Render::Shader shader = { "assets/shaders/Default.glsl" };
};


class Sandbox: public Application {
public:
    Sandbox(): Application("Sandbox", { 800, 450 }) {
        Log::SetPriority(Log::Level::TRACE);
        layers.Push(Unique<Runtime>());
    }
};

Unique<Application> Application::Create() {
    return Unique<Sandbox>();
}
