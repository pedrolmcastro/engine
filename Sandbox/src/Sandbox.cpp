#include "Configuration.hpp"
#include "Feather.hpp"

using namespace std;
using namespace Feather;


class SandboxLayer: public Layer::Layer {
public:
    void OnUpdate() override {
        Trace("Update");
    }

    void OnAttach() override {
        Error("Attach");
    }

    void OnDetach() override {
        Error("Detach");
    }

    void OnEvent(Event::Event& event) override {
        Event::Dispatcher dispatcher(event);
        dispatcher.Dispatch<Event::MouseMove>(Bind(OnMouseMove));
    }

    bool OnMouseMove(Event::MouseMove& event) {
        Info("%.2f %.2f", event.GetX(), event.GetY());
        return false;
    }
};


class Sandbox: public Application {
public:
    Sandbox() {
        Push(Unique<SandboxLayer>());
    }

    ~Sandbox() {

    }
};

Unique<Application> Application::Create() {
    return Unique<Sandbox>();
}
