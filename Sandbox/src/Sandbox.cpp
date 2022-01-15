#include "Engine.hpp"

using namespace Engine;


class Sandbox : public Application {
public:
    Sandbox() {

    }

    ~Sandbox() {

    }
};

Application *Application::create() {
    return new Sandbox();
}
