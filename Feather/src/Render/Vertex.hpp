#pragma once


#include "Precompiled.hpp"
#include "Core/Memory.hpp"
#include "Render/Index.hpp"
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


    class Array {
    public:
        Array();
        ~Array();

        void Bind() const;
        void Unbind() const;

        void AddVertex(Shared<Vertex::Buffer> vertex);
        const std::vector<Shared<Vertex::Buffer>>& GetVertex() const { return vertex; }

        void SetIndex(Shared<Index::Buffer> index);
        Shared<Index::Buffer> GetIndex() const { return index; }
    private:
        unsigned array;
        std::size_t position = 0;
        Shared<Index::Buffer> index = nullptr;
        std::vector<Shared<Vertex::Buffer>> vertex;
    };
}
