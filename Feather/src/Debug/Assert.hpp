#pragma once


#include "Precompiled.hpp"
#include "Debug/Log.hpp"

#ifdef ASSERTING
    #define Assert(expression, message, ...) {                                                      \
        if (!(expression)) {                                                                        \
            Fatal("Assertion Failed: %s. File: %s. Line: %d", #expression, __FILE__, __LINE__);     \
            if (message != "") Fatal(message __VA_OPT__(,) __VA_ARGS__);                            \
            abort();                                                                                \
        }                                                                                           \
    }
#else
    #define Assert(...)
#endif
