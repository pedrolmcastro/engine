#pragma once


#include "Precompiled.hpp"
#include "Render/Shader.hpp"

namespace Feather::Render::Vertex {
    class Element {
    public:
		bool normalized;
		Shader::Data type;
		std::size_t size, offset = 0;

		Element(Shader::Data type, bool normalized = false): type(type), size(Shader::SizeOf(type)), normalized(normalized) {}
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
}
