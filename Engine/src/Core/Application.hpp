#pragma once


#include "Memory.hpp"

namespace Engine {
    class Application {
    public:
        Application();
        virtual ~Application();

        // Defined by the client
        static Scope<Application> create();

        void run();
    };
}
