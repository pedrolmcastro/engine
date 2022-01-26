#include "Core/Layer.hpp"
#include "Core/Memory.hpp"

using namespace std;
using namespace Feather;


Layer::Stack::~Stack() {
    for (Scope<Layer>& layer : layers) {
        layer->OnDetach();
    }
}

void Layer::Stack::Push(Scope<Layer> layer) {
    layer->OnAttach();
    layers.push_back(move(layer));
}

Scope<Layer::Layer> Layer::Stack::Pop() {
    if (layers.empty()) return Scope<Layer>{};

    Scope<Layer> layer = move(layers.back());
    layers.pop_back();

    layer->OnDetach();
    return layer;
}
