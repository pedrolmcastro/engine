#include "Precompiled.hpp"

#include "Core/Window.hpp"
#include "Core/Application.hpp"

#include "Input/Event.hpp"
#include "Input/Input.hpp"

#include "Debug/Log.hpp"

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

        auto [x, y] = Input::GetMousePosition();
        Log::Print(Log::Level::INFO, "%f\t%f", x, y);

        Log::Print(Log::Level::WARN, "A:\t%d", Input::IsKeyPressed(Key::A));
        Log::Print(Log::Level::WARN, "B0:\t%d", Input::IsMousePressed(Mouse::LEFT));
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
