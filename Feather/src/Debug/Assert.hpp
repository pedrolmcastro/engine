#pragma once


#include "Precompiled.hpp"
#include "Debug/Log.hpp"

#define __Assert__(expression, message) {                                                                                       \
    if (!(expression)) {                                                                                                        \
        Feather::Log::fatal("Assertion Failed: %s. File: %s. Line: %d. Message: %s", #expression, __FILE__, __LINE__, message); \
        abort();                                                                                                                \
    }                                                                                                                           \
}                                                                                                                               \

// Default Argument for the Message
#define __Assert1__(expression) __Assert__(expression, "")
#define __Assert2__(expression, message) __Assert__(expression, message)

// Hack for Default Arguments in Macros
#define __Get3rdArgument__(first, second, third, ...) third
#define __AssertChooser__(...) __Get3rdArgument__(__VA_ARGS__, __Assert2__, __Assert1__)

#define Assert(...) __AssertChooser__(__VA_ARGS__)(__VA_ARGS__)
