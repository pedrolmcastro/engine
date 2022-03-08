#include "Precompiled.hpp"

#include "Debug/Assert.hpp"

#include "Math/Vector.hpp"

#include "Render/Texture.hpp"

#include <glad/glad.h>
#include <stb_image.h>

using namespace std;
using namespace Feather;


Render::Texture::Surface::Surface(const Math::Unsigned2& size, Format format, Filter filter): Texture(size), format(format == Format::RGBA ? GL_RGBA : GL_RGB) {
    glCreateTextures(GL_TEXTURE_2D, 1, &texture);
    glTextureStorage2D(texture, 1, GL_RGBA8, size.x, size.y);

    glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, filter == Filter::LINEAR ? GL_LINEAR : GL_NEAREST);
    glTextureParameteri(texture, GL_TEXTURE_MAG_FILTER, filter == Filter::LINEAR ? GL_LINEAR : GL_NEAREST);

    glTextureParameteri(texture, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(texture, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

Render::Texture::Surface::Surface(const filesystem::path& path, Filter filter) {
    int width, height, channels;

    stbi_set_flip_vertically_on_load(true);
    stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
    
    // TODO: Add Error Texture
    Assert(data, "Failed to load texture image: ", path);

    size = { unsigned(width), unsigned(height) };
    GLenum internal;

    // TODO: Review Image Formats
    switch (channels) {
        case 3:
            format = GL_RGB;
            internal = GL_RGB8;
            break;
        
        case 4:
            format = GL_RGBA;
            internal = GL_RGBA8;
            break;
        
        default:
            Assert(false, "Invalid texture image format: ", path);
            break;
    }

    glCreateTextures(GL_TEXTURE_2D, 1, &texture);
    glTextureStorage2D(texture, 1, internal, width, height);

    glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, filter == Filter::LINEAR ? GL_LINEAR : GL_NEAREST);
    glTextureParameteri(texture, GL_TEXTURE_MAG_FILTER, filter == Filter::LINEAR ? GL_LINEAR : GL_NEAREST);

    glTextureParameteri(texture, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(texture, GL_TEXTURE_WRAP_T, GL_REPEAT);

    SetData(width * height * (format == GL_RGBA ? 4 : 3), data);
    stbi_image_free(data);
}

Render::Texture::Surface::~Surface() {
    Unbind();
    glDeleteTextures(1, &texture);
}


void Render::Texture::Surface::Bind(size_t slot) {
    // TODO: Validade Slot
    this->slot = slot;
    glBindTextureUnit(slot, texture);
}

void Render::Texture::Surface::Unbind() {
    if (slot != NONE) {
        glBindTextureUnit(slot, 0);
        slot = NONE;
    }
}


void Render::Texture::Surface::SetData(size_t size, const void* data) {
    Assert(size == this->size.x * this->size.y * (format == GL_RGBA ? 4 : 3), "Invalid texture data size: ", size);
    glTextureSubImage2D(texture, 0, 0, 0, this->size.x, this->size.y, format, GL_UNSIGNED_BYTE, data);
}
