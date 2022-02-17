#pragma once


#include "Precompiled.hpp"
#include "Core/Memory.hpp"
#include "Core/Event.hpp"
#include "Core/Time.hpp"

// TODO: Nested Classes
namespace Feather::Layer {
	enum class Type { LAYER, OVERLAY, };

	class Layer {
	public:
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Time delta) {}
		virtual void OnEvent(Event::Event& event) {}
	};

    class Stack {
    public:
        ~Stack();

        void Push(Unique<Layer> layer, Type type = Type::LAYER);
        Unique<Layer> Pop(Type type = Type::LAYER);

		std::vector<Unique<Layer>>::reverse_iterator rbegin() { return stack.rbegin(); }
		std::vector<Unique<Layer>>::reverse_iterator rend() { return stack.rend(); }
		std::vector<Unique<Layer>>::iterator begin() { return stack.begin(); }
		std::vector<Unique<Layer>>::iterator end() { return stack.end(); }
    private:
		std::size_t layers = 0;
		std::size_t overlays = 0;
        std::vector<Unique<Layer>> stack;
    };
}
