#pragma once


#include "Precompiled.hpp"

namespace Feather::Render::Vertex {
    class Buffer {
    public:
        Buffer(std::size_t size, const void* vertices = nullptr);
        ~Buffer();

        void Bind() const;
        void Unbind() const;

        void SetData(std::size_t size, const void* data);
    private:
        unsigned buffer;
    };
}
