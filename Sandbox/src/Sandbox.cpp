#include "Engine.hpp"

using namespace Engine;


class Sandbox : public Application {
public:
    Sandbox() {

    }

    ~Sandbox() {

    }
};

Scope<Application> Application::create() {
    return create_scope<Sandbox>();
}
