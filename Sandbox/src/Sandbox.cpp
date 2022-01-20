#include "Configuration.hpp"
#include "Feather.hpp"

using namespace std;
using namespace Feather;


class Sandbox : public Application {
public:
    Sandbox() {
        Log::SetPriority(Log::Level::TRACE);

        // Category
        Event::KeyPress event(Key::A);
        Trace("Window: %d", event.In(Event::Category::WINDOW));
        Trace("Input: %d", event.In(Event::Category::INPUT));
        Trace("Mouse: %d", event.In(Event::Category::MOUSE));
        Trace("Key: %d", event.In(Event::Category::KEY));

        // Window
        Event::WindowResize window_resize(0, 0);
        Event::WindowEnter window_enter;
        Event::WindowLeave window_leave;
        Event::WindowClose window_close;
        Info(string(window_resize).c_str());
        Info(string(window_enter).c_str());
        Info(string(window_leave).c_str());
        Info(string(window_close).c_str());

        // Mouse
        Event::MousePress mouse_press(Mouse::LEFT);
        Event::MouseRelease mouse_release(Mouse::LEFT);
        Event::MouseScroll mouse_scroll(.0f, .0f);
        Event::MouseMove mouse_move(.0f, .0f);
        Warn(string(mouse_press).c_str());
        Warn(string(mouse_release).c_str());
        Warn(string(mouse_scroll).c_str());
        Warn(string(mouse_move).c_str());

        // Key
        Event::KeyPress key_press(Key::D0);
        Event::KeyRelease key_release(Key::D0);
        Error(string(key_press).c_str());
        Error(string(key_release).c_str());
    }

    ~Sandbox() {

    }
};

Scope<Application> Application::Create() {
    return CreateScope<Sandbox>();
}
