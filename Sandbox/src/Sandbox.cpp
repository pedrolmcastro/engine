#include "Configuration.hpp"
#include "Feather.hpp"

using namespace std;
using namespace Feather;


class Main: public Layer::Layer {
public:
    Main(const Window& window): window(window) {}

    void OnUpdate() override {
        Trace("%d", window.IsMinimized());
    }
private:
    const Window& window;
};


class Sandbox: public Application {
public:
    Sandbox(): Application("Sandbox", { 800, 450 }) {
        Log::SetPriority(Log::Level::TRACE);
        layers.Push(Unique<Main>(window));
    }
};

Unique<Application> Application::Create() {
    return Unique<Sandbox>();
}
