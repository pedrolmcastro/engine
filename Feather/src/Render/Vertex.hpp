#pragma once


#include "Precompiled.hpp"
#include "Core/Memory.hpp"
#include "Render/Index.hpp"
#include "Render/Shader.hpp"

namespace Feather::Render::Vertex {
    class Element {
    public:
		bool normalized;
		Shader::Data type;
		std::size_t size, offset = 0;

		Element(Shader::Data type, bool normalized = false): type(type), size(Shader::SizeOf(type)), normalized(normalized) {}
		operator Shader::Data() const { return type; }
    };


    class Layout {
    public:
		Layout(std::initializer_list<Element> elements);

		std::size_t GetStride() const { return stride; }
		const std::vector<Element>& GetElements() const { return elements; }

		std::vector<Element>::const_iterator begin() const { return elements.begin(); }
		std::vector<Element>::const_iterator end() const { return elements.end(); }
		std::vector<Element>::iterator begin() { return elements.begin(); }
		std::vector<Element>::iterator end() { return elements.end(); }
	private:
		std::vector<Element> elements;
		std::size_t stride;
    };


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

        void AddVertex(Unique<Vertex::Buffer> vertex);
        const std::vector<Unique<Vertex::Buffer>>& GetVertex() const { return vertex; }

        void SetIndex(Unique<Index::Buffer> index);
        const Index::Buffer& GetIndex() const { return *index; }
    private:
        unsigned array;
        std::size_t position = 0;
        Unique<Index::Buffer> index = nullptr;
        std::vector<Unique<Vertex::Buffer>> vertex;
    };
}
