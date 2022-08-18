#include "Core/Application.hpp"


int main() {
    std::unique_ptr<Feather::Application> application = Feather::Application::Create();
    application->Run();

    return 0;
}
