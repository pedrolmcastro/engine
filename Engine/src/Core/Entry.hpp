#include "Application.hpp"


int main() {
    Engine::Application *application = Engine::Application::create();
    application->run();

    delete application;
    return 0;
}
