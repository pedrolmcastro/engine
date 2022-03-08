#include "Precompiled.hpp"

#include "Debug/Assert.hpp"

#include "Math/Matrix.hpp"
#include "Math/Vector.hpp"

#include "Render/Shader.hpp"

#include <glad/glad.h>

using namespace std;
using namespace Feather;


size_t Render::Shader::CountOf(Data data) {
    switch (data) {
        case Data::BOOL:  return 1;
        case Data::BOOL2: return 2;
        case Data::BOOL3: return 3;
        case Data::BOOL4: return 4;

        case Data::INT:  return 1;
        case Data::INT2: return 2;
        case Data::INT3: return 3;
        case Data::INT4: return 4;

        case Data::UNSIGNED:  return 1;
        case Data::UNSIGNED2: return 2;
        case Data::UNSIGNED3: return 3;
        case Data::UNSIGNED4: return 4;

        case Data::FLOAT:  return 1;
        case Data::FLOAT2: return 2;
        case Data::FLOAT3: return 3;
        case Data::FLOAT4: return 4;

        case Data::DOUBLE:  return 1;
        case Data::DOUBLE2: return 2;
        case Data::DOUBLE3: return 3;
        case Data::DOUBLE4: return 4;

        case Data::MATRIX2: return 2;
        case Data::MATRIX3: return 3;
        case Data::MATRIX4: return 4;
    }

    Assert(false, "Unknown shader data type: ", static_cast<std::underlying_type<Data>::type>(data));
    return 0;
}

size_t Render::Shader::SizeOf(Data data) {
    switch (data) {
        case Data::BOOL:  return sizeof(bool) * 1;
        case Data::BOOL2: return sizeof(bool) * 2;
        case Data::BOOL3: return sizeof(bool) * 3;
        case Data::BOOL4: return sizeof(bool) * 4;

        case Data::INT:  return sizeof(int) * 1;
        case Data::INT2: return sizeof(int) * 2;
        case Data::INT3: return sizeof(int) * 3;
        case Data::INT4: return sizeof(int) * 4;

        case Data::UNSIGNED:  return sizeof(unsigned) * 1;
        case Data::UNSIGNED2: return sizeof(unsigned) * 2;
        case Data::UNSIGNED3: return sizeof(unsigned) * 3;
        case Data::UNSIGNED4: return sizeof(unsigned) * 4;

        case Data::FLOAT:  return sizeof(float) * 1;
        case Data::FLOAT2: return sizeof(float) * 2;
        case Data::FLOAT3: return sizeof(float) * 3;
        case Data::FLOAT4: return sizeof(float) * 4;

        case Data::DOUBLE:  return sizeof(double) * 1;
        case Data::DOUBLE2: return sizeof(double) * 2;
        case Data::DOUBLE3: return sizeof(double) * 3;
        case Data::DOUBLE4: return sizeof(double) * 4;

        case Data::MATRIX2: return sizeof(float) * 2 * 2;
        case Data::MATRIX3: return sizeof(float) * 3 * 3;
        case Data::MATRIX4: return sizeof(float) * 4 * 4;
    }

    Assert(false, "Unknown shader data type: ", static_cast<std::underlying_type<Data>::type>(data));
    return 0;
}

GLenum Render::Shader::TypeOf(Data data) {
    switch (data) {
        case Data::BOOL     ... Data::BOOL4:     return GL_UNSIGNED_BYTE;
        case Data::INT      ... Data::INT4:      return GL_INT;
        case Data::UNSIGNED ... Data::UNSIGNED4: return GL_UNSIGNED_INT;
        case Data::FLOAT    ... Data::FLOAT4:    return GL_FLOAT;
        case Data::DOUBLE   ... Data::DOUBLE4:   return GL_DOUBLE;
        case Data::MATRIX2  ... Data::MATRIX4:   return GL_FLOAT;
    }

    Assert(false, "Unknown shader data type: ", static_cast<std::underlying_type<Data>::type>(data));
    return 0;
}

GLenum Render::Shader::TypeOf(const std::string& type) {
    // TODO: Review Shader Types
    if (type == "vertex")   return GL_VERTEX_SHADER;
    if (type == "pixel")    return GL_FRAGMENT_SHADER;

    Assert(false, "Unknown shader type: ", type);
    return 0;
}


Render::Shader::Shader(const string& vertex, const string& fragment) {
    unordered_map<GLenum, string> sources;
    sources[GL_VERTEX_SHADER] = vertex;
    sources[GL_FRAGMENT_SHADER] = fragment;

    Compile(sources);
}

Render::Shader::Shader(const filesystem::path& path) {
    string file = Read(path);
    unordered_map<GLenum, string> sources = Split(file);

    Compile(sources);
}

Render::Shader::~Shader() {
    Unbind();
    glDeleteProgram(program);
}


void Render::Shader::Bind() const {
    glUseProgram(program);
}

void Render::Shader::Unbind() const {
    glUseProgram(0);
}


string Render::Shader::Read(const filesystem::path& path) const {
    ifstream file(path);
    Assert(file, "Failed to open shader file: ", path);

    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

unordered_map<GLenum, string> Render::Shader::Split(const string& file) const {
    unordered_map<GLenum, string> sources;
    size_t position = file.find("#type");

    while (position != string::npos) {
        size_t endofline = file.find_first_of("\r\n", position);
        Assert(endofline != string::npos, "Expected new line after shader type!");

        size_t begin = position + 6;
        string type = file.substr(begin, endofline - begin);

        size_t next = file.find_first_not_of("\r\n", endofline);
        Assert(next != string::npos, "Expected source code after shader type!");

        position = file.find("#type", next);
        sources[TypeOf(type)] = position == string::npos ? file.substr(next) : file.substr(next, position - next);
    }

    return sources;
}


void Render::Shader::Compile(const unordered_map<GLenum, string>& sources) {
    program = glCreateProgram();
    // TODO: Review Number of Shaders
    std::array<GLenum, 2> shaders;


    size_t index = 0;
    for (auto[type, source] : sources) {
        unsigned shader = glCreateShader(type);

        const char* cstring = source.c_str();
        glShaderSource(shader, 1, &cstring, 0);

        glCompileShader(shader);

        int compiled;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

        if (compiled == GL_FALSE) {
            int length;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

            vector<char> message(length);
            glGetShaderInfoLog(shader, length, &length, message.data());

            for (GLenum previous : shaders) {
                glDeleteShader(previous);
            }
            glDeleteShader(shader);
            glDeleteProgram(program);
            program = 0;

            Assert(false, "Failed to compile shader: ", message.data());
            return;
        }

        glAttachShader(program, shader);
        shaders[index++] = shader;
    }


    glLinkProgram(program);

    int linked;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);

    if (linked == GL_FALSE) {
        int length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

        vector<char> message(length);
        glGetProgramInfoLog(program, length, &length, message.data());

        for (GLenum shader : shaders) {
            glDeleteShader(shader);
        }
        glDeleteProgram(program);
        program = 0;

        Assert(false, "Failed to compile shader: ", message.data());
        return;
    }


    for (GLenum shader : shaders) {
        glDetachShader(program, shader);
        glDeleteShader(shader);
    }
}


void Render::Shader::Upload(const string& name, int value) const {
    Bind();
	glUniform1i(glGetUniformLocation(program, name.c_str()), value);
}

void Render::Shader::Upload(const string& name, const Math::Int2& values) const {
    Bind();
	glUniform2i(glGetUniformLocation(program, name.c_str()), values.x, values.y);
}

void Render::Shader::Upload(const string& name, const Math::Int3& values) const {
    Bind();
	glUniform3i(glGetUniformLocation(program, name.c_str()), values.x, values.y, values.z);
}

void Render::Shader::Upload(const string& name, const Math::Int4& values) const {
    Bind();
	glUniform4i(glGetUniformLocation(program, name.c_str()), values.x, values.y, values.z, values.w);
}


void Render::Shader::Upload(const string& name, unsigned value) const {
    Bind();
	glUniform1ui(glGetUniformLocation(program, name.c_str()), value);
}

void Render::Shader::Upload(const string& name, const Math::Unsigned2& values) const {
    Bind();
	glUniform2ui(glGetUniformLocation(program, name.c_str()), values.x, values.y);
}

void Render::Shader::Upload(const string& name, const Math::Unsigned3& values) const {
    Bind();
	glUniform3ui(glGetUniformLocation(program, name.c_str()), values.x, values.y, values.z);
}

void Render::Shader::Upload(const string& name, const Math::Unsigned4& values) const {
    Bind();
	glUniform4ui(glGetUniformLocation(program, name.c_str()), values.x, values.y, values.z, values.w);
}


void Render::Shader::Upload(const string& name, float value) const {
    Bind();
	glUniform1f(glGetUniformLocation(program, name.c_str()), value);
}

void Render::Shader::Upload(const string& name, const Math::Float2& values) const {
    Bind();
	glUniform2f(glGetUniformLocation(program, name.c_str()), values.x, values.y);
}

void Render::Shader::Upload(const string& name, const Math::Float3& values) const {
    Bind();
	glUniform3f(glGetUniformLocation(program, name.c_str()), values.x, values.y, values.z);
}

void Render::Shader::Upload(const string& name, const Math::Float4& values) const {
    Bind();
	glUniform4f(glGetUniformLocation(program, name.c_str()), values.x, values.y, values.z, values.w);
}


void Render::Shader::Upload(const string& name, const Math::Matrix2& values) const {
    Bind();
	glUniformMatrix2fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, values);
}

void Render::Shader::Upload(const string& name, const Math::Matrix3& values) const {
    Bind();
    glUniformMatrix3fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, values);
}

void Render::Shader::Upload(const string& name, const Math::Matrix4& values) const {
    Bind();
    glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, values);
}
