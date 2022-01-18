#include "Precompiled.hpp"

#include "Log.hpp"
#include "Assert.hpp"
#include "Application.hpp"

using namespace Engine;
using namespace std;


Application::Application() {

}

Application::~Application() {
    
}

void Application::run() {
    int variable = 0;

    assert(variable == 0);
    assert(variable == 1);
}
