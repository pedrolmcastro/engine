#include "Precompiled.hpp"

#include "Core/Event.hpp"
#include "Core/Layer.hpp"
#include "Core/Application.hpp"

#include "Input/Input.hpp"

#include "Math/Vector.hpp"

#include "Render/Window.hpp"

using namespace std;
using namespace Feather;


Application::Application(const string& name, Math::Vector2 size, bool vsync): window(name, size, Bind(OnEvent), vsync) {
    Input::SetWindow(window);
}

void Application::Run() {
    while (running) {
        window.OnUpdate();

        if (!window.IsMinimized()) {
            for (Unique<Layer::Layer>& layer : layers) {
                layer->OnUpdate();
            }
        }
    }
}

void Application::OnEvent(Event::Event& event) {
    Event::Dispatcher dispatcher(event);
    dispatcher.Dispatch<Event::WindowClose>(Bind(OnWindowClose));

    for (auto it = layers.rbegin(); it != layers.rend() && !event.handled; it++) {
        (*it)->OnEvent(event);
    }
}

bool Application::OnWindowClose(Event::WindowClose& event) {
    Close();
    return true;
}
