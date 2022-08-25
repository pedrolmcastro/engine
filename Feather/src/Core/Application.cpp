#include "Precompiled.hpp"

#include "Core/Event.hpp"
#include "Core/Layer.hpp"
#include "Core/Application.hpp"


void Feather::Application::Run() {
    while (running) {
        const auto now = std::chrono::steady_clock::now();
        const std::chrono::duration<float> deltatime = now - lastframe;
        lastframe = now;

        std::ranges::for_each(layers, [=](auto& layer){ layer->OnUpdate(deltatime); });
    }
}

void Feather::Application::Dispatch(Event& event) {
    for (auto it = layers.rbegin(); it != layers.rend() && !event.handled; ++it) {
        (*it)->OnEvent(event);
    }
}
