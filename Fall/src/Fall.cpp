#include "Feather.hpp"

using namespace std;
using namespace Feather;


class Runtime: public Layer {
public:
    Runtime(): window("Feather Fall", { 800, 800 }) {}


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

        vertexarray.AddVertex(make_unique<Render::Vertex::Buffer>(layout, sizeof(vertices), vertices));
        vertexarray.SetIndex(make_unique<Render::Index::Buffer>(sizeof(indices), indices));

        shader.Upload("u_Texture", 0);
    }

    void OnUpdate(Time delta) override {
        shader.Bind();
        texture.Bind();
        vertexarray.Bind();

        Render::Command::Clear();
        Render::Command::Draw(vertexarray);

        window.OnUpdate();
    }


    void OnEvent(Event& event) override {
        Event::Dispatcher dispatcher(event);
        dispatcher.Dispatch<Event::KeyPress>(BindEvent(OnKeyPress));
        dispatcher.Dispatch<Event::WindowClose>(BindEvent(OnWindowClose));
    }

    bool OnKeyPress(Event::KeyPress& event) {
        if (event.GetKey() == Input::Key::ESCAPE) {
            Application::Close();
            return true;
        }

        return false;
    }

    bool OnWindowClose(Event::WindowClose& event) {
        Application::Close();
        return true;
    }

private:
    Render::Window window;
    Render::Vertex::Array vertexarray;
    Render::Shader shader = { "assets/shaders/Default.glsl" };
    Render::Texture::Surface texture = { "assets/textures/Checkerboard.png", Render::Texture::Filter::NEAREST };
};


class Fall: public Application {
public:
    Fall() {
        Debug::Logger::Client().priority = Debug::Logger::Level::TRACE;

        Trace("Trace");
        Info("Info");
        Warn("Warn");
        Error("Error");
        Fatal("Fatal");

        layers.Push(make_unique<Runtime>());
    }
};

unique_ptr<Application> Application::Create() {
    return make_unique<Fall>();
}
