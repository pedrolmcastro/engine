#include "Precompiled.hpp"

#include "Core/Memory.hpp"

#include "Render/Index.hpp"
#include "Render/Shader.hpp"
#include "Render/Vertex.hpp"

#include <glad/glad.h>

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


Render::Vertex::Buffer::Buffer(const Layout& layout, size_t size, const void* vertices): layout(layout) {
    glCreateBuffers(1, &buffer);

    Bind();
    glBufferData(GL_ARRAY_BUFFER, size, vertices, vertices == nullptr ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}

Render::Vertex::Buffer::~Buffer() {
    Unbind();
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
    Unbind();
    glDeleteVertexArrays(1, &array);
}

void Render::Vertex::Array::Bind() const {
    glBindVertexArray(array);
}

void Render::Vertex::Array::Unbind() const {
    glBindVertexArray(0);
}

void Render::Vertex::Array::AddVertex(Unique<Vertex::Buffer> vertex) {
    Bind();
    vertex->Bind();

    const Layout& layout = vertex->GetLayout();
    size_t stride = layout.GetStride();

    for (const Element& element : layout) {
        switch(element.type) {
            case Shader::Data::BOOL ... Shader::Data::UNSIGNED4: {
                glEnableVertexAttribArray(position);
                glVertexAttribIPointer(position, Shader::CountOf(element), Shader::TypeOf(element), stride, (const void*)element.offset);
                position++;
                break;
            }
            
            case Shader::Data::FLOAT ... Shader::Data::DOUBLE4: {
                glEnableVertexAttribArray(position);
			    glVertexAttribPointer(position, Shader::CountOf(element), Shader::TypeOf(element), element.normalized, stride, (const void*)element.offset);
			    position++;
			    break;
            }

            case Shader::Data::MATRIX2 ... Shader::Data::MATRIX4: {
                size_t count = Shader::CountOf(element);

                for (size_t i = 0; i < count; i++) {
                    glEnableVertexAttribArray(position);
                    glVertexAttribPointer(position, count, Shader::TypeOf(element), element.normalized, stride, (const void*)(element.offset + sizeof(float) * count * i));
                    glVertexAttribDivisor(position, 1);
                    position++;
                }
                break;
            }
        }
    }

    this->vertex.push_back(move(vertex));
}

void Render::Vertex::Array::SetIndex(Unique<Index::Buffer> index) {
    Bind();
    index->Bind();

    this->index = move(index);
}
