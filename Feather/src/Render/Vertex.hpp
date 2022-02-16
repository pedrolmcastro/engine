#pragma once


#include "Precompiled.hpp"
#include "Render/Layout.hpp"

namespace Feather::Render::Vertex {
    class Buffer {
    public:
        Buffer(const Layout& layout, std::size_t size, const void* vertices = nullptr);
        ~Buffer();

        void Bind() const;
        void Unbind() const;

        void SetData(std::size_t size, const void* data);
        const Layout& GetLayout() const { return layout; }
    private:
        unsigned buffer;
        Layout layout;
    };
}
