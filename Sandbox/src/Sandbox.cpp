#include "Feather.hpp"

using namespace std;
using namespace Feather;


class Runtime: public Layer {
public:
    void OnAttach() override {
        Event::WindowFocus windowfocus;
        Trace("Window: ", windowfocus.In(Event::Category::WINDOW));
        Trace("Input:  ", windowfocus.In(Event::Category::INPUT));
        Trace("Mouse:  ", windowfocus.In(Event::Category::MOUSE));
        Trace("None:   ", windowfocus.In(Event::Category::NONE));
        Trace("Key:    ", windowfocus.In(Event::Category::KEY));

        Event::MousePress mousepress(Input::Mouse::B0);
        Info("Window: ", mousepress.In(Event::Category::WINDOW));
        Info("Input:  ", mousepress.In(Event::Category::INPUT));
        Info("Mouse:  ", mousepress.In(Event::Category::MOUSE));
        Info("None:   ", mousepress.In(Event::Category::NONE));
        Info("Key:    ", mousepress.In(Event::Category::KEY));

        Event::KeyPress keypress(Input::Key::A, false);
        Warn("Window: ", keypress.In(Event::Category::WINDOW));
        Warn("Input:  ", keypress.In(Event::Category::INPUT));
        Warn("Mouse:  ", keypress.In(Event::Category::MOUSE));
        Warn("None:   ", keypress.In(Event::Category::NONE));
        Warn("Key:    ", keypress.In(Event::Category::KEY));


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
