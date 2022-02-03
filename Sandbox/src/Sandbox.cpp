#include "Configuration.hpp"
#include "Feather.hpp"

using namespace std;
using namespace Feather;


class Main: public Layer::Layer {
public:
    void OnEvent(Event::Event& event) override {
        Event::Dispatcher dispatcher(event);
        dispatcher.Dispatch<Event::WindowFocus>(Bind(OnWindowFocus));
        dispatcher.Dispatch<Event::WindowUnfocus>(Bind(OnWindowUnfocus));
        dispatcher.Dispatch<Event::WindowHover>(Bind(OnWindowHover));
        dispatcher.Dispatch<Event::WindowUnhover>(Bind(OnWindowUnhover));
    }

    bool OnWindowFocus(Event::WindowFocus& event) {
        Trace(string(event).c_str());
        return false;
    }

    bool OnWindowUnfocus(Event::WindowUnfocus& event) {
        Info(string(event).c_str());
        return false;
    }

    bool OnWindowHover(Event::WindowHover& event) {
        Warn(string(event).c_str());
        return false;
    }

    bool OnWindowUnhover(Event::WindowUnhover& event) {
        Error(string(event).c_str());
        return false;
    }
};


class Sandbox: public Application {
public:
    Sandbox(): Application("Sandbox", { 800, 450 }) {
        Log::SetPriority(Log::Level::TRACE);
        Push(Unique<Main>());
    }

    ~Sandbox() {

    }
};

Unique<Application> Application::Create() {
    return Unique<Sandbox>();
}
