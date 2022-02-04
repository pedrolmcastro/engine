#include "Configuration.hpp"
#include "Feather.hpp"

using namespace std;
using namespace Feather;


class Runtime: public Layer::Layer {
public:
    void OnEvent(Event::Event& event) override {
        Event::Dispatcher dispatcher(event);
        dispatcher.Dispatch<Event::KeyPress>(Bind(OnKeyPress));
    }

    bool OnKeyPress(Event::KeyPress& event) {
        Trace("Layer");
        return false;
    }
};

class Overlay: public Layer::Layer {
public:
    void OnEvent(Event::Event& event) override {
        Event::Dispatcher dispatcher(event);
        dispatcher.Dispatch<Event::KeyPress>(Bind(OnKeyPress));
    }

    bool OnKeyPress(Event::KeyPress& event) {
        Trace("Overlay");
        return true;
    }
};


class Sandbox: public Application {
public:
    Sandbox(): Application("Sandbox", { 800, 450 }) {
        Log::SetPriority(Log::Level::TRACE);

        layers.Push(Unique<Overlay>(), Layer::Type::OVERLAY);
        layers.Push(Unique<Runtime>());
    }
};

Unique<Application> Application::Create() {
    return Unique<Sandbox>();
}
