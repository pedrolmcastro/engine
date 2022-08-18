#pragma once


#include "Precompiled.hpp"

#include "Core/Event.hpp"
#include "Core/Layer.hpp"
#include "Render/Context.hpp"


int main();

namespace Feather {
    class Application {
    public:
        friend int ::main();
        virtual ~Application() = default;

        // Defined by the client
        static std::unique_ptr<Application> Create();

        static void Dispatch(Event& event);
        static void Close() { running = false; }
    protected:
        inline static Render::Context context; // Destroyed after layers windows
        inline static Layer::Stack layers;
    private:
        inline static bool running = true;
        inline static std::chrono::high_resolution_clock clock;
        inline static std::chrono::high_resolution_clock::time_point last = clock.now();

        static void Run();
    };
}
