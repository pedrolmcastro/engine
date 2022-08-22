#pragma once


#include "Precompiled.hpp"
#include "Debug/Logger.hpp"

#define Unused(variable) ((void)(variable))

#ifdef ASSERTING
    #define Assert(expression, ...) {                                                           \
        if (!(expression)) {                                                                    \
            Fatal("Assertion Failed: ", #expression, ".File: ", __FILE__, ".Line: ", __LINE__); \
            __VA_OPT__(Fatal(__VA_ARGS__);)                                                     \
            abort();                                                                            \
        }                                                                                       \
    }
#else
    #define Assert(expression, ...)
#endif
