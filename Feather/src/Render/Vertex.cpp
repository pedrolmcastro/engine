#include "Precompiled.hpp"

#include "Render/Layout.hpp"
#include "Render/Vertex.hpp"

#include <glad/glad.h>

using namespace std;
using namespace Feather;


Render::Vertex::Buffer::Buffer(const Layout& layout, size_t size, const void* vertices): layout(layout) {
    glCreateBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, vertices == nullptr ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}

Render::Vertex::Buffer::~Buffer() {
    glDeleteBuffers(1, &buffer);
}

void Render::Vertex::Buffer::Bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
}

void Render::Vertex::Buffer::Unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Render::Vertex::Buffer::SetData(size_t size, const void* data) {
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}
