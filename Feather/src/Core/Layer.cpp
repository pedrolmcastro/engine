#include "Core/Layer.hpp"
#include "Core/Memory.hpp"

using namespace std;
using namespace Feather;


Layer::Stack::~Stack() {
    for (Unique<Layer>& layer : layers) {
        layer->OnDetach();
    }
}

void Layer::Stack::Push(Unique<Layer> layer) {
    layer->OnAttach();
    layers.push_back(move(layer));
}

Unique<Layer::Layer> Layer::Stack::Pop() {
    if (layers.empty()) return nullptr;

    Unique<Layer> layer = move(layers.back());
    layers.pop_back();

    layer->OnDetach();
    return layer;
}
