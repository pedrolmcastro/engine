#include "Precompiled.hpp"

#include "Core/Event.hpp"
#include "Core/Layer.hpp"
#include "Core/Application.hpp"

#include "Input/Input.hpp"

#include "Math/Vector.hpp"

#include "Render/Window.hpp"

// Temporary
#include "Render/Shader.hpp"
#include "glad/glad.h"

using namespace std;
using namespace Feather;


Application::Application(const string& name, Math::Vector2 size, bool vsync): window(name, size, BindEvent(OnEvent), vsync), shader("assets/shaders/Default.glsl") {
    Input::SetWindow(window);

    // Temporary

    glGenVertexArrays(1, &vertexarray);
    glBindVertexArray(vertexarray);

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

    float vertices[3 * 3] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

    glGenBuffers(1, &indexbuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);

    unsigned indices[3] = { 0, 1, 2 };
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void Application::Run() {
    while (running) {
        window.OnUpdate();

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.Bind();
        glBindVertexArray(vertexarray);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

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
