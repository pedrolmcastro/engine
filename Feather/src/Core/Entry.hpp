#include "Core/Application.hpp"


int main() {
    Feather::Scope<Feather::Application> application = Feather::Application::create();
    application->run();

    return 0;
}
