#pragma once


#include "Precompiled.hpp"
#include "Log.hpp"

#define __assert__(expression, message) {                                                                                       \
    if (!(expression)) {                                                                                                        \
        Feather::Log::fatal("Assertion Failed: %s. File: %s. Line: %d. Message: %s", #expression, __FILE__, __LINE__, message); \
        abort();                                                                                                                \
    }                                                                                                                           \
}                                                                                                                               \

// Default Argument for the Message
#define __assert_1__(expression) __assert__(expression, "")
#define __assert_2__(expression, message) __assert__(expression, message)

// Hack for Default Arguments in Macros
#define __get_3rd_argument__(first, second, third, ...) third
#define __assert_chooser__(...) __get_3rd_argument__(__VA_ARGS__, __assert_2__, __assert_1__)

#define assert(...) __assert_chooser__(__VA_ARGS__)(__VA_ARGS__)
