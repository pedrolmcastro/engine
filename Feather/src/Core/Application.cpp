#include "Precompiled.hpp"

#include "Core/Time.hpp"
#include "Core/Event.hpp"
#include "Core/Layer.hpp"
#include "Core/Application.hpp"

#include "Render/Command.hpp"

using namespace std;
using namespace Feather;


void Application::Run() {
    while (running) {
        chrono::high_resolution_clock::time_point now = clock.now();
        Time delta(chrono::duration<float>(now - last).count());
        last = now;

        for (unique_ptr<Layer>& layer : layers) {
            layer->OnUpdate(delta);
        }
    }
}

void Application::Dispatch(Event& event) {
    for (auto it = layers.rbegin(); it != layers.rend() && !event.handled; it++) {
        (*it)->OnEvent(event);
    }
}
