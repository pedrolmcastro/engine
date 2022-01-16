#include "Precompiled.hpp"

#include "Log.hpp"
#include "Application.hpp"

using namespace Engine;
using namespace std;


Application::Application() {

}

Application::~Application() {
    
}

void Application::run() {
    Log::set_level(Log::Level::TRACE);

    Log::trace("Trace");
    Log::info("Info");
    Log::warn("Warn");
    Log::error("Error");
    Log::fatal("Fatal");

    int variable = 0;
    Log::trace("%s: %d", "Format", variable);
}
