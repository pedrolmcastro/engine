#include "Core/Layer.hpp"
#include "Core/Memory.hpp"

using namespace std;
using namespace Feather;


Layer::Stack::~Stack() {
    for (Unique<Layer>& layer : stack) {
        layer->OnDetach();
    }
}

void Layer::Stack::Push(Unique<Layer> layer, Type type) {
    layer->OnAttach();

    if (type == Type::LAYER) {
        stack.insert(stack.begin() + layers, move(layer));
        layers++;
    }
    else {
        stack.push_back(move(layer));
        overlays++;
    }
}

Unique<Layer> Layer::Stack::Pop(Type type) {
    if (type == Type::LAYER && layers == 0 || type == Type::OVERLAY && overlays == 0) return nullptr;

    Unique<Layer> layer = nullptr;

    if (type == Type::LAYER) {
        layers--;
        layer = move(stack[layers]);
        stack.erase(stack.begin() + layers);
    }
    else {
        overlays--;
        layer = move(stack.back());
        stack.pop_back();
    }

    layer->OnDetach();
    return layer;
}
