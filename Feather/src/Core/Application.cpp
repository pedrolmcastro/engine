#include "Precompiled.hpp"

#include "Core/Layer.hpp"
#include "Core/Application.hpp"

#include "Input/Event.hpp"
#include "Input/Input.hpp"

#include "Render/Window.hpp"

using namespace std;
using namespace Feather;


Application::Application(string name, unsigned width, unsigned height, bool vsync): window(name, width, height, vsync, Bind(OnEvent)) {
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
