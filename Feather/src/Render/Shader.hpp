#pragma once


#include "Precompiled.hpp"
typedef unsigned GLenum;

namespace Feather::Render {
    class Shader {
    public:
        // TODO: Add Integer Data Types
        enum class Data { FLOAT, VECTOR2, VECTOR3, VECTOR4, MATRIX2, MATRIX3, MATRIX4, };
        static std::size_t CountOf(Data data);
        static std::size_t SizeOf(Data data);
        static GLenum TypeOf(Data data);

        Shader(const std::string& vertex, const std::string& fragment);
        Shader(const std::filesystem::path& path);
        ~Shader();

        void Bind() const;
        void Unbind() const;
    private:
        unsigned program = 0;

        static GLenum TypeOf(const std::string& type);

        std::string Read(const std::filesystem::path& path) const;
        std::unordered_map<GLenum, std::string> Split(const std::string& file) const;

        void Compile(const std::unordered_map<GLenum, std::string>& sources);
    };
}
