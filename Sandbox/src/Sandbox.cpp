#include "Configuration.hpp"
#include "Feather.hpp"

using namespace std;
using namespace Feather;


class Main: public Layer::Layer {
public:
    void OnAttach() override {
        Math::Vector3 first(36, 49, 1);
        Math::Vector3 second(64, 2, 2);
        Info("%.2f", Math::Angle(first, second));
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
