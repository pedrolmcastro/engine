#pragma once


#include "Precompiled.hpp"

#define assert(expression, message) {                                   \
    if (!(expression)) {                                                \
        Engine::Assert::log(#expression, __FILE__, __LINE__, message);  \
        abort();                                                        \
    }                                                                   \
}                                                                       \

namespace Engine::Assert {
    void log(const char *expression, const char *file, int line, const char *message);
}
