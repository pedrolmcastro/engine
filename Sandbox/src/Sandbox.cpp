#include "Feather.hpp"

using namespace std;
using namespace Feather;


class Runtime: public Layer {
public:
    void OnAttach() override {
        Render::Vertex::Layout layout = {
            { Render::Shader::Data::FLOAT3 }, // a_Position
            { Render::Shader::Data::FLOAT2 }, // a_TextureCoordinate
        };

        float vertices[4 * (3 + 2)] = {
            -0.5f, -0.5f, 0.0f,  0.0f, 0.0f,
            -0.5f,  0.5f, 0.0f,  0.0f, 1.0f,
             0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
             0.5f,  0.5f, 0.0f,  1.0f, 1.0f,
        };

        unsigned indices[2 * 3] = {
            0, 1, 2,
            1, 2, 3,
        };

        vertexarray.AddVertex(Unique<Render::Vertex::Buffer>(layout, sizeof(vertices), vertices));
        vertexarray.SetIndex(Unique<Render::Index::Buffer>(sizeof(indices), indices));

        shader.Upload("u_Texture", 0);
    }

    void OnUpdate(Time delta) override {
        shader.Bind();
        texture.Bind();
        vertexarray.Bind();

        Render::Command::Draw(vertexarray);
    }

    void OnEvent(Event& event) override {
        Event::Dispatcher dispatcher(event);
    }
private:
    Render::Vertex::Array vertexarray;
    Render::Shader shader = { "assets/shaders/Default.glsl" };
    Render::Texture::Surface texture = { "assets/textures/Checkerboard.png", Render::Texture::Filter::NEAREST };
};


class Sandbox: public Application {
public:
    Sandbox(): Application("Sandbox", { 800, 800 }) {
        Debug::Log::SetPriority(Debug::Log::Level::TRACE);
        layers.Push(Unique<Runtime>());
    }
};

Unique<Application> Application::Create() {
    return Unique<Sandbox>();
}
