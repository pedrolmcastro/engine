#include "Configuration.hpp"
#include "Feather.hpp"

using namespace std;
using namespace Feather;


class Runtime: public Layer::Layer {
public:
    void OnAttach() override {
        Math::Vector3 vector(1.0f);
        Math::Vector4 translated = Math::Translate({ 1, 2, 3, }) * Math::Vector4(vector, 1.0f);

        Trace("%s", string(translated).c_str());
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
