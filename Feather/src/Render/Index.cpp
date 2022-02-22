#include "Precompiled.hpp"

#include "Render/Index.hpp"

#include <glad/glad.h>

using namespace std;
using namespace Feather;


Render::Index::Buffer::Buffer(size_t size, const unsigned* vertices): count(size / sizeof(unsigned)) {
    glCreateBuffers(1, &buffer);

    Bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

Render::Index::Buffer::~Buffer() {
    glDeleteBuffers(1, &buffer);
}

void Render::Index::Buffer::Bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
}

void Render::Index::Buffer::Unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
