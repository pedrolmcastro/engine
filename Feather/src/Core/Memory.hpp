#pragma once


#include "Precompiled.hpp"

namespace Feather {
	template<typename T> class Unique {
	public:
		Unique(std::nullptr_t): pointer(nullptr) {}
		template<typename U> Unique(Unique<U>& other) = delete;
		template<typename U> Unique(Unique<U>&& other): pointer(std::move(other.pointer)) {}
		template<typename ...Args> Unique(Args&&... args) { pointer = std::make_unique<T>(std::forward<Args>(args)...); }


		T* operator->() const { return pointer.get(); }
		T& operator*() const { return *pointer.get(); }
		T& operator[](std::size_t i) const { return pointer.get()[i]; }

		template<typename U> bool operator==(const Unique<U>& other) { return pointer == other.pointer; }
		template<typename U> bool operator!=(const Unique<U>& other) { return pointer != other.pointer; }

		operator bool() const { return bool(pointer); }
	private:
		template<typename U> friend class Unique;
		std::unique_ptr<T> pointer;
	};


	template<typename T> class Shared {
	public:
		Shared(std::nullptr_t): pointer(nullptr) {}
		template<typename U> Shared(Shared<U>& other): pointer(other.pointer) {}
		template<typename U> Shared(Shared<U>&& other): pointer(std::move(other.pointer)) {}
		template<typename ...Args> Shared(Args&&... args) { pointer = std::make_shared<T>(std::forward<Args>(args)...); }


		std::size_t Count() { return pointer.use_count(); }


		T* operator->() const { return pointer.get(); }
		T& operator*() const { return *pointer.get(); }
		T& operator[](std::size_t i) const { return pointer.get()[i]; }

		template<typename U> bool operator==(const Shared<U>& other) { return pointer == other.pointer; }
		template<typename U> bool operator!=(const Shared<U>& other) { return pointer != other.pointer; }

		operator bool() const { return bool(pointer); }
	private:
		template<typename U> friend class Shared;
		std::shared_ptr<T> pointer;
	};
}
