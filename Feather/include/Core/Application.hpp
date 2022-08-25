#pragma once


#include <chrono>
#include <memory>

#include "Core/Event.hpp"
#include "Core/Layer.hpp"
#include "Render/Context.hpp"


int main();

namespace Feather {
    class Application {
    public:
        friend int ::main(); // Allow call to .Run()

        Application(const Application& other) = delete;
        Application(Application&& other) = delete;
        virtual ~Application() = default;

        static std::unique_ptr<Application> Create(); // Defined by the client

        static void Dispatch(Event& event);
        static void Close() { running = false; }

    private:
        inline static Render::Context context; // Destroyed after layers windows

    protected:
        Application() = default;
        inline static Layer::Stack layers;

    private:
        inline static auto lastframe = std::chrono::steady_clock::now();
        inline static auto running = true;

        static void Run();
    };
}
