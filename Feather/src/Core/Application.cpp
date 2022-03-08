#include "Precompiled.hpp"

#include "Core/Time.hpp"
#include "Core/Event.hpp"
#include "Core/Layer.hpp"
#include "Core/Application.hpp"

#include "Input/Input.hpp"

#include "Render/Window.hpp"
#include "Render/Command.hpp"

using namespace std;
using namespace Feather;


Application::Application(const string& title, Math::Unsigned2 size, bool vsync): window(title, size, BindEvent(OnEvent), vsync) {
    Input::SetWindow(window);
}

void Application::Run() {
    while (running) {
        window.OnUpdate();
        Render::Command::Clear();

        chrono::high_resolution_clock::time_point now = clock.now();
        Time delta(chrono::duration<float>(now - last).count());
        last = now;

        if (!window.IsMinimized()) {
            for (unique_ptr<Layer>& layer : layers) {
                layer->OnUpdate(delta);
            }
        }
    }
}

void Application::OnEvent(Event& event) {
    Event::Dispatcher dispatcher(event);
    dispatcher.Dispatch<Event::WindowClose>(BindEvent(OnWindowClose));
    dispatcher.Dispatch<Event::WindowResize>(BindEvent(OnWindowResize));

    for (auto it = layers.rbegin(); it != layers.rend() && !event.handled; it++) {
        (*it)->OnEvent(event);
    }
}

bool Application::OnWindowClose(Event::WindowClose& event) {
    Close();
    return true;
}

bool Application::OnWindowResize(Event::WindowResize& event) {
    Render::Command::SetViewport(0, 0, event.GetWidth(), event.GetHeight());
    return false;
}
