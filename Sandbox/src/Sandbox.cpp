#include "Configuration.hpp"
#include "Feather.hpp"

using namespace std;
using namespace Feather;


class Runtime: public Layer::Layer {
public:
    void OnAttach() override {
        
    }

    void OnUpdate() override {

    }

    void OnEvent(Event::Event& event) override {
        Event::Dispatcher dispatcher(event);
    }
};


class Sandbox: public Application {
public:
    Sandbox(): Application("Sandbox", { 800.0f, 450.0f }) {
        Log::SetPriority(Log::Level::TRACE);
        layers.Push(Unique<Runtime>());
    }
};

Unique<Application> Application::Create() {
    return Unique<Sandbox>();
}
