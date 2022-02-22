#include "Precompiled.hpp"

#include "Math/Vector.hpp"

#include "Render/API.hpp"
#include "Render/Vertex.hpp"

#include <glad/glad.h>

using namespace std;
using namespace Feather;


void Render::API::Draw(const Vertex::Array& vertex) {
    glDrawElements(GL_TRIANGLES, vertex.GetIndex()->GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Render::API::Draw(const Vertex::Array& vertex, size_t count) {
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
}


void Render::API::Clear(const Math::Float4& color) {
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT);
}


void Render::API::SetViewport(size_t x, size_t y, size_t width, size_t height) {
    glViewport(x, y, width, height);
}
