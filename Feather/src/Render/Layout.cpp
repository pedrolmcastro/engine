#include "Precompiled.hpp"

#include "Render/Layout.hpp"

using namespace std;
using namespace Feather;


Render::Vertex::Layout::Layout(std::initializer_list<Element> elements): elements(elements) {
    size_t offset = 0;
    stride = 0;

    for (Element& element : this->elements) {
        element.offset = offset;

        offset += element.size;
        stride += element.size;
    }
}
