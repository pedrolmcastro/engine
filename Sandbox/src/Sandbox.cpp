#include "Configuration.hpp"
#include "Feather.hpp"

using namespace std;
using namespace Feather;


class Runtime: public Layer::Layer {
public:
    void OnAttach() override {
        Math::Vector3 vector(1.0f);

        Math::Vector3 axis(1.0f, 2.0f, 3.0f);
        float angle = 4.0f;

        Math::Vector4 bymatrix = Math::Rotate(axis, angle) * vector;
        Trace(string(bymatrix).c_str());
        
        Math::Vector3 byquaternion = Math::Quaternion(axis, angle) * vector;
        Trace(string(byquaternion).c_str());
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
