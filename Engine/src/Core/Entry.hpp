#include "Application.hpp"


int main() {
    Engine::Scope<Engine::Application> application = Engine::Application::create();
    application->run();

    return 0;
}
