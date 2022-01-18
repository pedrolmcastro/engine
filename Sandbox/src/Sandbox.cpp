#include "Feather.hpp"

using namespace Feather;


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
