#include "Precompiled.hpp"

#include "Core/Window.hpp"
#include "Core/Application.hpp"

#include "Input/Event.hpp"

using namespace std;
using namespace Feather;


Application::Application(): window("Window", 800, 450, true, Bind(OnEvent)) {

}

Application::~Application() {
    
}

void Application::Run() {
    while (running) {
        window.OnUpdate();
    }
}

void Application::OnEvent(Event::Event& event) {
    Event::Dispatcher dispatcher(event);
    dispatcher.Dispatch<Event::WindowClose>(Bind(OnWindowClose));
}

bool Application::OnWindowClose(Event::WindowClose& event) {
    running = false;
    return true;
}
