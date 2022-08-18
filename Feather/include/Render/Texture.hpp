#pragma once


#include "Precompiled.hpp"
#include "Math/Vector.hpp"
typedef unsigned GLenum;

// TODO: Volume and Cube Texture
namespace Feather::Render {
    class Texture {
    public:
        static const std::size_t NONE = SIZE_MAX;


        enum class Filter { LINEAR, NEAREST, };
        enum class Format { RGB, RGBA, };

        class Surface;


        Texture() = default;
        Texture(const Math::Unsigned2& size): size(size) {}

        virtual ~Texture() = default;


        unsigned GetWidth() const { return size.x; }
        unsigned GetHeight() const { return size.y; }
        Math::Unsigned2 GetSize() const { return size; }

        virtual void SetData(std::size_t size, const void* data) = 0;


        virtual void Bind(std::size_t slot = 0) = 0;
        virtual void Unbind() = 0;
    protected:
        Math::Unsigned2 size;
    };


    class Texture::Surface: public Texture {
    public:
        Surface(const Math::Unsigned2& size, Format format = Format::RGBA, Filter filter = Filter::LINEAR);
        Surface(const std::filesystem::path& path, Filter filter = Filter::LINEAR);
        ~Surface();

        void Bind(std::size_t slot = 0) override;
        void Unbind() override;

        void SetData(std::size_t size, const void* data) override;
    private:
        GLenum format;
        unsigned texture;
        std::size_t slot = NONE;
    };
}
