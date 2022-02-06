#include "Configuration.hpp"
#include "Feather.hpp"

using namespace std;
using namespace Feather;


class Runtime: public Layer::Layer {
public:
    void OnAttach() override {
        Math::Vector3 vector(1);
        Trace("%s", string(- vector).c_str());
    }
};


class Sandbox: public Application {
public:
    Sandbox(): Application("Sandbox", { 800, 450 }) {
        Log::SetPriority(Log::Level::TRACE);
        layers.Push(Unique<Runtime>());
    }
};

Unique<Application> Application::Create() {
    return Unique<Sandbox>();
}
