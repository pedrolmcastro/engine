#include "Precompiled.hpp"

#include "Core/Event.hpp"
#include "Core/Application.hpp"

#include "Debug/Log.hpp"

#include "Input/Key.hpp"
#include "Input/Mouse.hpp"

using namespace Feather;
using namespace std;


Application::Application() {

}

Application::~Application() {
    
}

void Application::Run() {
    // Category
    Event::KeyPress event(Key::A);
    Log::Trace("Window: %d", event.In(Event::Category::WINDOW));
    Log::Trace("Input: %d", event.In(Event::Category::INPUT));
    Log::Trace("Mouse: %d", event.In(Event::Category::MOUSE));
    Log::Trace("Key: %d", event.In(Event::Category::KEY));

    // Window
    Event::WindowResize window_resize(0, 0);
    Event::WindowEnter window_enter;
    Event::WindowLeave window_leave;
    Event::WindowClose window_close;
    Log::Info(string(window_resize).c_str());
    Log::Info(string(window_enter).c_str());
    Log::Info(string(window_leave).c_str());
    Log::Info(string(window_close).c_str());

    // Mouse
    Event::MousePress mouse_press(Mouse::LEFT);
    Event::MouseRelease mouse_release(Mouse::LEFT);
    Event::MouseScroll mouse_scroll(.0f, .0f);
    Event::MouseMove mouse_move(.0f, .0f);
    Log::Warn(string(mouse_press).c_str());
    Log::Warn(string(mouse_release).c_str());
    Log::Warn(string(mouse_scroll).c_str());
    Log::Warn(string(mouse_move).c_str());

    // Key
    Event::KeyPress key_press(Key::D0);
    Event::KeyRelease key_release(Key::D0);
    Log::Error(string(key_press).c_str());
    Log::Error(string(key_release).c_str());
}
