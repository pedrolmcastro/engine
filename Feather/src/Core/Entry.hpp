#include "Core/Application.hpp"


int main() {
    Feather::Scope<Feather::Application> application = Feather::Application::Create();
    application->Run();

    return 0;
}
