#include "Precompiled.hpp"

#include "Debug/Assert.hpp"

#include "Render/Shader.hpp"

#include <glad/glad.h>

using namespace std;
using namespace Feather;


size_t Render::Shader::CountOf(Data data) {
    switch (data) {
        case Shader::Data::FLOAT:   return 1;
        case Shader::Data::VECTOR2: return 2;
        case Shader::Data::VECTOR3: return 3;
        case Shader::Data::VECTOR4: return 4;
        case Shader::Data::MATRIX2: return 2;
        case Shader::Data::MATRIX3: return 3;
        case Shader::Data::MATRIX4: return 4;
    }

    Assert(false, "Unknown shader data type!");
    return 0;
}

size_t Render::Shader::SizeOf(Data data) {
    switch (data) {
        case Data::FLOAT:   return sizeof(float);
        case Data::VECTOR2: return sizeof(float) * 2;
        case Data::VECTOR3: return sizeof(float) * 3;
        case Data::VECTOR4: return sizeof(float) * 4;
        case Data::MATRIX2: return sizeof(float) * 2 * 2;
        case Data::MATRIX3: return sizeof(float) * 3 * 3;
        case Data::MATRIX4: return sizeof(float) * 4 * 4;
    }

    Assert(false, "Unknown shader data type!");
    return 0;
}

GLenum Render::Shader::TypeOf(Data data) {
    switch (data) {
        case Data::FLOAT:   return GL_FLOAT;
        case Data::VECTOR2: return GL_FLOAT;
        case Data::VECTOR3: return GL_FLOAT;
        case Data::VECTOR4: return GL_FLOAT;
        case Data::MATRIX2: return GL_FLOAT;
        case Data::MATRIX3: return GL_FLOAT;
        case Data::MATRIX4: return GL_FLOAT;
    }

    Assert(false, "Unknown shader data type!");
    return 0;
}

GLenum Render::Shader::TypeOf(const std::string& type) {
    // TODO: Review Shader Types
    if (type == "vertex")                       return GL_VERTEX_SHADER;
    if (type == "fragment" || type == "pixel")  return GL_FRAGMENT_SHADER;

    // TODO: Use std::format()
    stringstream stream;
    stream << "Unknown shader type: " << type;
    Assert(false, stream.str().c_str());
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
    // TODO: Use std::format()
    stringstream stream;
    stream << "Failed to open file: " << path;
    Assert(file, stream.str().c_str());

    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

unordered_map<GLenum, string> Render::Shader::Split(const string& file) const {
    unordered_map<GLenum, string> sources;
    size_t position = file.find("#type");

    while (position != string::npos) {
        size_t endofline = file.find_first_of("\r\n", position);
        Assert(endofline != string::npos, "Expected new line after shader type");
        
        size_t begin = position + 6;
        string type = file.substr(begin, endofline - begin);

        size_t next = file.find_first_not_of("\r\n", endofline);
        Assert(next != string::npos, "Expected source code after shader type");

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

            // TODO: Use std::format()
            stringstream stream;
            stream << "Failed to compile shader: " << message.data();
            Assert(false, stream.str().c_str());
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

        // TODO: Use std::format()
        stringstream stream;
        stream << "Failed to compile shader: " << message.data();
        Assert(false, stream.str().c_str());
        return;
    }


    for (GLenum shader : shaders) {
        glDetachShader(program, shader);
        glDeleteShader(shader);
    }
}
