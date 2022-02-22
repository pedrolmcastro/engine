#include "Precompiled.hpp"

#include "Core/Memory.hpp"

#include "Render/Layout.hpp"
#include "Render/Shader.hpp"
#include "Render/Vertex.hpp"

#include <glad/glad.h>

using namespace std;
using namespace Feather;


Render::Vertex::Buffer::Buffer(const Layout& layout, size_t size, const void* vertices): layout(layout) {
    glCreateBuffers(1, &buffer);

    Bind();
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
    Bind();
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}


Render::Vertex::Array::Array() {
    glCreateVertexArrays(1, &array);
    Bind();
}

Render::Vertex::Array::~Array() {
    glDeleteVertexArrays(1, &array);
}

void Render::Vertex::Array::Bind() const {
    glBindVertexArray(array);
}

void Render::Vertex::Array::Unbind() const {
    glBindVertexArray(0);
}

void Render::Vertex::Array::AddVertex(Shared<Vertex::Buffer> vertex) {
    Bind();
    vertex->Bind();

    const Layout& layout = vertex->GetLayout();
    size_t stride = layout.GetStride();

    for (const Element& element : layout) {
        switch(element.type) {
            case Shader::Data::FLOAT ... Shader::Data::VECTOR4: {
                glEnableVertexAttribArray(position);
			    glVertexAttribPointer(position, Shader::CountOf(element.type), Shader::TypeOf(element.type), element.normalized, stride, (const void*)element.offset);
				position++;
			    break;
            }

            case Shader::Data::MATRIX2 ... Shader::Data::MATRIX4: {
                size_t count = Shader::CountOf(element.type);

                for (size_t i = 0; i < count; i++) {
                    glEnableVertexAttribArray(position);
                    glVertexAttribPointer(position, count, Shader::TypeOf(element.type), element.normalized, stride, (const void*)(element.offset + sizeof(float) * count * i));
                    glVertexAttribDivisor(position, 1);
                    position++;
                }
                break;
            }
        }
    }

    this->vertex.push_back(vertex);
}

void Render::Vertex::Array::SetIndex(Shared<Index::Buffer> index) {
    Bind();
    index->Bind();

    this->index = index;
}
