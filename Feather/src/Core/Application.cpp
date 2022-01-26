#include "Precompiled.hpp"

#include "Core/Layer.hpp"
#include "Core/Window.hpp"
#include "Core/Application.hpp"

#include "Input/Event.hpp"
#include "Input/Input.hpp"

using namespace std;
using namespace Feather;


Application::Application(): window("Window", 800, 450, true, Bind(OnEvent)) {
    Input::SetWindow(window);
}

Application::~Application() {
    
}

void Application::Run() {
    while (running) {
        window.OnUpdate();

        for (Unique<Layer::Layer>& layer : layers) {
            layer->OnUpdate();
        }
    }
}

void Application::OnEvent(Event::Event& event) {
    Event::Dispatcher dispatcher(event);
    dispatcher.Dispatch<Event::WindowClose>(Bind(OnWindowClose));

    for (auto it = layers.rbegin(); it != layers.rend(); it++) {
        if (event.handled) break;
        (*it)->OnEvent(event);
    }
}

bool Application::OnWindowClose(Event::WindowClose& event) {
    running = false;
    return true;
}
