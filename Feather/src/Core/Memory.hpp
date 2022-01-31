#pragma once


#include "Precompiled.hpp"

namespace Feather {
	template<typename T> class Unique {
	public:
		Unique(std::nullptr_t): pointer(nullptr) {}
		template<typename U> Unique(Unique<U>& other) = delete;
		template<typename U> Unique(Unique<U>&& other): pointer(std::move(other.pointer)) {}
		template<typename ...Args> Unique(Args&&... args) { pointer = std::make_unique<T>(std::forward<Args>(args)...); }

		T* operator ->() const { return pointer.get(); }
		T& operator *() const { return *pointer.get(); }
		T& operator [](std::size_t i) const { return pointer.get()[i]; }

		operator bool() const { return bool(pointer); }
	private:
		std::unique_ptr<T> pointer;
		template<typename U> friend class Unique;
	};


	template<typename T> class Shared {
	public:
		Shared(std::nullptr_t): pointer(nullptr) {}
		template<typename U> Shared(Shared<U>& other): pointer(other.pointer) {}
		template<typename U> Shared(Shared<U>&& other): pointer(std::move(other.pointer)) {}
		template<typename ...Args> Shared(Args&&... args) { pointer = std::make_shared<T>(std::forward<Args>(args)...); }

		std::size_t Count() { return pointer.use_count(); }

		T* operator ->() const { return pointer.get(); }
		T& operator *() const { return *pointer.get(); }
		T& operator [](std::size_t i) const { return pointer.get()[i]; }

		operator bool() const { return bool(pointer); }
	private:
		std::shared_ptr<T> pointer;
		template<typename U> friend class Shared;
	};
}
