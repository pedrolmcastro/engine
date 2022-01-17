#include "Precompiled.hpp"

#include "Logger.hpp"
#include "Application.hpp"

using namespace Engine;
using namespace std;


Application::Application() {

}

Application::~Application() {
    
}

void Application::run() {
    Logger::prioritize(Logger::Level::TRACE);

    Logger::trace("Trace");
    Logger::info("Info");
    Logger::warn("Warn");
    Logger::error("Error");
    Logger::fatal("Fatal");

    int variable = 0;
    Logger::trace("%s: %d", "Format", variable);
}
