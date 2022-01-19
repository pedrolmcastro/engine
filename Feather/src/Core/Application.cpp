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

void Application::run() {
    // Category
    Event::KeyPress event(Key::A);
    Log::trace("Window: %d", event.in_category(Event::Category::WINDOW));
    Log::trace("Input: %d", event.in_category(Event::Category::INPUT));
    Log::trace("Mouse: %d", event.in_category(Event::Category::MOUSE));
    Log::trace("Key: %d", event.in_category(Event::Category::KEY));

    // Window
    Event::WindowResize window_resize(0, 0);
    Event::WindowEnter window_enter;
    Event::WindowLeave window_leave;
    Event::WindowClose window_close;
    Log::info(string(window_resize).c_str());
    Log::info(string(window_enter).c_str());
    Log::info(string(window_leave).c_str());
    Log::info(string(window_close).c_str());

    // Mouse
    Event::MousePress mouse_press(Mouse::LEFT);
    Event::MouseRelease mouse_release(Mouse::LEFT);
    Event::MouseScroll mouse_scroll(.0f, .0f);
    Event::MouseMove mouse_move(.0f, .0f);
    Log::warn(string(mouse_press).c_str());
    Log::warn(string(mouse_release).c_str());
    Log::warn(string(mouse_scroll).c_str());
    Log::warn(string(mouse_move).c_str());

    // Key
    Event::KeyPress key_press(Key::D0);
    Event::KeyRelease key_release(Key::D0);
    Log::error(string(key_press).c_str());
    Log::error(string(key_release).c_str());
}
