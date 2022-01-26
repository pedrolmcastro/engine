#include "Core/Application.hpp"


int main() {
    Feather::Unique<Feather::Application> application = Feather::Application::Create();
    application->Run();

    return 0;
}
