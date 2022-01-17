#include "Precompiled.hpp"

#include "Assert.hpp"
#include "Logger.hpp"


void Engine::Assert::log(const char *expression, const char *file, int line, const char *message) {
    Logger::fatal("Assertion Failed: %s. File: %s. Line: %d. Message: %s", expression, file, line, message);
}
