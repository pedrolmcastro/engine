#include "Precompiled.hpp"

#include "Core/Event.hpp"
#include "Core/Layer.hpp"
#include "Core/Application.hpp"

#include "Input/Input.hpp"

#include "Render/Window.hpp"

// Temporary
#include "Render/Index.hpp"
#include "Render/Vertex.hpp"
#include "Render/Layout.hpp"
#include "Render/Shader.hpp"
#include <glad/glad.h>

using namespace std;
using namespace Feather;


Application::Application(const string& name, Math::Vector2 size, bool vsync): window(name, size, BindEvent(OnEvent), vsync) {
    Input::SetWindow(window);

    // Temporary

    glGenVertexArrays(1, &vertexarray);
    glBindVertexArray(vertexarray);


    Render::Vertex::Layout layout = {
        { Render::Shader::Data::VECTOR3 }, // a_Position
        { Render::Shader::Data::VECTOR4 }, // a_Color
    };

    float vertices[3 * (3 + 4)] = {
        -0.5f, -0.5f, 0.0f,  0.8f, 0.2f, 0.2f, 1.0f,
         0.5f, -0.5f, 0.0f,  0.2f, 0.8f, 0.2f, 1.0f,
         0.0f,  0.5f, 0.0f,  0.2f, 0.2f, 0.8f, 1.0f,
    };

    vertexbuffer = Unique<Render::Vertex::Buffer>(layout, sizeof(vertices), vertices);


    // TODO: Add Matrix Support
    size_t index = 0;
    for (Render::Vertex::Element& element : layout) {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, Render::Shader::CountOf(element.type), Render::Shader::TypeOf(element.type), element.normalized, layout.GetStride(), (const void*)element.offset);
        index++;
    }


    unsigned indices[3] = { 0, 1, 2, };
    indexbuffer = Unique<Render::Index::Buffer>(sizeof(indices), indices);
}

void Application::Run() {
    while (running) {
        window.OnUpdate();

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.Bind();
        glBindVertexArray(vertexarray);
        glDrawElements(GL_TRIANGLES, indexbuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

        if (!window.IsMinimized()) {
            for (Unique<Layer::Layer>& layer : layers) {
                layer->OnUpdate();
            }
        }
    }
}

void Application::OnEvent(Event::Event& event) {
    Event::Dispatcher dispatcher(event);
    dispatcher.Dispatch<Event::WindowClose>(BindEvent(OnWindowClose));

    for (auto it = layers.rbegin(); it != layers.rend() && !event.handled; it++) {
        (*it)->OnEvent(event);
    }
}

bool Application::OnWindowClose(Event::WindowClose& event) {
    Close();
    return true;
}
