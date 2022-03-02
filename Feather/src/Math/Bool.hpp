#pragma once


#include "Precompiled.hpp"
#include "Debug/Assert.hpp"

// TODO: Use operator<<()
namespace Feather::Math {
    class Bool2 {
    public:
        union { bool x, s, u, r; };
        union { bool y, t, v, g; };


        Bool2(bool x, bool y): x(x), y(y) {}
        Bool2(bool scalar = false): x(scalar), y(scalar) {}


        Bool2 operator!() { return Bool2(!x, !y); }
        Bool2 operator&&(const Bool2& other) { return Bool2(x && other.x, y && other.y); }
        Bool2 operator||(const Bool2& other) { return Bool2(x || other.x, y || other.y); }


        bool& operator[](std::size_t index) {
            switch(index) {
                case 0: return x;
                case 1: return y;
            }

            Assert(index < 2, "Invalid vector index: %lu", index);
            return x;
        }

        bool operator[](std::size_t index) const {
            switch(index) {
                case 0: return x;
                case 1: return y;
            }

            Assert(index < 2, "Invalid vector index: %lu", index);
            return 0;
        }


        operator std::string() const {
            std::stringstream stream;
            stream << '[' << x << ", " << y << ']';
            return stream.str();
        }


        bool All() const { return x && y; }
        bool Any() const { return x || y; }
        bool None() const { return !Any(); }
    };


    class Bool3 {
    public:
        union { bool x, s, u, r; };
        union { bool y, t, v, g; };
        union { bool z, p, w, b; };


        Bool3(bool x, bool y, bool z): x(x), y(y), z(z) {}
        Bool3(bool scalar = false): x(scalar), y(scalar), z(scalar) {}
        Bool3(const Bool2& vector, bool z = false): x(vector.x), y(vector.y), z(z) {}


        Bool3 operator!() { return Bool3(!x, !y, !z); }
        Bool3 operator&&(const Bool3& other) { return Bool3(x && other.x, y && other.y, z && other.z); }
        Bool3 operator||(const Bool3& other) { return Bool3(x || other.x, y || other.y, z || other.z); }


        bool& operator[](std::size_t index) {
            switch(index) {
                case 0: return x;
                case 1: return y;
                case 2: return z;
            }

            Assert(index < 3, "Invalid vector index: %lu", index);
            return x;
        }

        bool operator[](std::size_t index) const {
            switch(index) {
                case 0: return x;
                case 1: return y;
                case 2: return z;
            }

            Assert(index < 3, "Invalid vector index: %lu", index);
            return 0;
        }


        operator std::string() const {
            std::stringstream stream;
            stream << '[' << x << ", " << y << ", " << z << ']';
            return stream.str();
        }


        bool All() const { return x && y && z; }
        bool Any() const { return x || y || z; }
        bool None() const { return !Any(); }
    };


    class Bool4 {
    public:
        union { bool x, s, r; };
        union { bool y, t, g; };
        union { bool z, p, b; };
        union { bool w, q, a; };


        Bool4(bool x, bool y, bool z, bool w): x(x), y(y), z(z), w(w) {}
        Bool4(bool scalar = false): x(scalar), y(scalar), z(scalar), w(scalar) {}
        Bool4(const Bool3& vector, bool w = false): x(vector.x), y(vector.y), z(vector.z), w(w) {}


        Bool4 operator!() { return Bool4(!x, !y, !z, !w); }
        Bool4 operator&&(const Bool4& other) { return Bool4(x && other.x, y && other.y, z && other.z, w && other.w); }
        Bool4 operator||(const Bool4& other) { return Bool4(x || other.x, y || other.y, z || other.z, w || other.w); }


        bool& operator[](std::size_t index) {
            switch(index) {
                case 0: return x;
                case 1: return y;
                case 2: return z;
                case 3: return w;
            }

            Assert(index < 4, "Invalid vector index: %lu", index);
            return x;
        }

        bool operator[](std::size_t index) const {
            switch(index) {
                case 0: return x;
                case 1: return y;
                case 2: return z;
                case 3: return w;
            }

            Assert(index < 4, "Invalid vector index: %lu", index);
            return 0;
        }


        operator std::string() const {
            std::stringstream stream;
            stream << '[' << x << ", " << y << ", " << z << ", " << w << ']';
            return stream.str();
        }


        bool All() const { return x && y && z && w; }
        bool Any() const { return x || y || z || w; }
        bool None() const { return !Any(); }
    };
}
