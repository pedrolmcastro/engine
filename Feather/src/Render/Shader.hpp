#pragma once


#include "Precompiled.hpp"
#include "Math/Matrix.hpp"
#include "Math/Vector.hpp"
typedef unsigned GLenum;

namespace Feather::Render {
    class Shader {
    public:
        enum class Data {
            BOOL, BOOL2, BOOL3, BOOL4, INT, INT2, INT3, INT4, UNSIGNED, UNSIGNED2, UNSIGNED3, UNSIGNED4,
            FLOAT, FLOAT2, FLOAT3, FLOAT4, DOUBLE, DOUBLE2, DOUBLE3, DOUBLE4, MATRIX2, MATRIX3, MATRIX4,
        };

        static std::size_t CountOf(Data data);
        static std::size_t SizeOf(Data data);
        static GLenum TypeOf(Data data);


        Shader(const std::string& vertex, const std::string& fragment);
        Shader(const std::filesystem::path& path);
        ~Shader();


        void Bind() const;
        void Unbind() const;


        void Upload(const std::string& name, int value) const;
        void Upload(const std::string& name, const Math::Int2& values) const;
        void Upload(const std::string& name, const Math::Int3& values) const;
        void Upload(const std::string& name, const Math::Int4& values) const;
        
        void Upload(const std::string& name, unsigned value) const;
        void Upload(const std::string& name, const Math::Unsigned2& values) const;
        void Upload(const std::string& name, const Math::Unsigned3& values) const;
        void Upload(const std::string& name, const Math::Unsigned4& values) const;

        void Upload(const std::string& name, float value) const;
        void Upload(const std::string& name, const Math::Float2& values) const;
        void Upload(const std::string& name, const Math::Float3& values) const;
        void Upload(const std::string& name, const Math::Float4& values) const;

        void Upload(const std::string& name, const Math::Matrix2& values) const;
        void Upload(const std::string& name, const Math::Matrix3& values) const;
        void Upload(const std::string& name, const Math::Matrix4& values) const;
    private:
        unsigned program = 0;


        static GLenum TypeOf(const std::string& type);


        std::string Read(const std::filesystem::path& path) const;
        std::unordered_map<GLenum, std::string> Split(const std::string& file) const;

        void Compile(const std::unordered_map<GLenum, std::string>& sources);
    };
}
