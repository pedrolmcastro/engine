#pragma once


#include "Precompiled.hpp"
#include "Core/Memory.hpp"
#include "Input/Event.hpp"

namespace Feather::Layer {

	class Layer {
	public:
		Layer() = default;
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event::Event& event) {}
	};

    class Stack {
    public:
        Stack() = default;
        ~Stack();

        void Push(Unique<Layer> layer);
        Unique<Layer> Pop();

        std::vector<Unique<Layer>>::iterator begin() { return layers.begin(); }
		std::vector<Unique<Layer>>::iterator end() { return layers.end(); }

		std::vector<Unique<Layer>>::reverse_iterator rbegin() { return layers.rbegin(); }
		std::vector<Unique<Layer>>::reverse_iterator rend() { return layers.rend(); }
    private:
        std::vector<Unique<Layer>> layers;
    };
}
