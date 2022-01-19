#pragma once


#include "Core/Memory.hpp"

namespace Feather {
    class Application {
    public:
        Application();
        virtual ~Application();

        // Defined by the client
        static Scope<Application> create();

        void run();
    };
}
