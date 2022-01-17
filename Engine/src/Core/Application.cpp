#include "Precompiled.hpp"

#include "Assert.hpp"
#include "Logger.hpp"
#include "Application.hpp"

using namespace Engine;
using namespace std;


Application::Application() {

}

Application::~Application() {
    
}

void Application::run() {
    int variable = 0;

    assert(variable == 0, "Variable is not zero");
    assert(variable == 1, "Variable is not one");
}
