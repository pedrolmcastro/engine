#pragma once


#include "Precompiled.hpp"

namespace Feather::Render::Index {
    class Buffer {
    public:
        Buffer(std::size_t size, const unsigned* vertices);
        ~Buffer();

        void Bind() const;
        void Unbind() const;

        std::size_t GetCount() const { return count; }
    private:
        unsigned buffer;
        std::size_t count;
    };
}
