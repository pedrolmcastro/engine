#pragma once


#include "Precompiled.hpp"

#include "Math/Vector.hpp"

#include "Render/API.hpp"
#include "Render/Vertex.hpp"

// TODO: Command Queue
// TODO: Multithreading
namespace Feather::Render {
    class Command {
    public:
        static void Draw(const Vertex::Array& vertex) { API::Draw(vertex); }
        static void Draw(const Vertex::Array& vertex, std::size_t count) { API::Draw(vertex, count); }

        static void Clear(const Math::Float4& color = { 0.0f, 0.0f, 0.0f, 1.0f }) { API::Clear(color); }

        static void SetViewport(std::size_t x, std::size_t y, std::size_t width, std::size_t height) { API::SetViewport(x, y, width, height); }
    };
}
