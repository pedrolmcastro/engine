#pragma once


#include "Precompiled.hpp"
typedef unsigned GLenum;

namespace Feather::Render {
    class Shader {
    public:
        Shader(const std::string& vertex, const std::string& fragment);
        Shader(const std::filesystem::path& path);
        ~Shader();

        void Bind() const;
        void Unbind() const;
    private:
        unsigned program = 0;

        GLenum StringToType(const std::string& type) const;
        std::string Read(const std::filesystem::path& path) const;
        std::unordered_map<GLenum, std::string> Split(const std::string& file) const;

        void Compile(const std::unordered_map<GLenum, std::string>& sources);
    };
}
