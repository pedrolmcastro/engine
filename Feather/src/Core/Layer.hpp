#pragma once


#include "Precompiled.hpp"
#include "Core/Memory.hpp"
#include "Input/Event.hpp"

namespace Feather::Layer {

	class Layer {
	public:
		Layer(std::string name): name(name) {}
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event::Event& event) {}

        operator std::string() const { return name; }
	private:
		std::string name;
	};

    class Stack {
    public:
        Stack() = default;
        ~Stack();

        void Push(Scope<Layer> layer);
        Scope<Layer> Pop();

        std::vector<Scope<Layer>>::iterator begin() { return layers.begin(); }
		std::vector<Scope<Layer>>::iterator end() { return layers.end(); }

		std::vector<Scope<Layer>>::reverse_iterator rbegin() { return layers.rbegin(); }
		std::vector<Scope<Layer>>::reverse_iterator rend() { return layers.rend(); }
    private:
        std::vector<Scope<Layer>> layers;
    };
}
