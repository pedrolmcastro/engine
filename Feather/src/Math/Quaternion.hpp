#pragma once


#include "Precompiled.hpp"

#include "Math/Bool.hpp"
#include "Math/Vector.hpp"
#include "Debug/Assert.hpp"

// TODO: Use operator<<()
namespace Feather::Math {
    class Quaternion {
    public:
        float x, y, z, w;


        Quaternion(const Float3& angles);
        Quaternion(const Float3& axis, float angle);
        Quaternion(const Float3& first, const Float3& second);
        Quaternion(float x, float y, float z, float w): x(x), y(y), z(z), w(w) {}
        Quaternion(float scalar = 0.0f): x(scalar), y(scalar), z(scalar), w(scalar) {}

        static Quaternion Identity() { return Quaternion(0.0f, 0.0f, 0.0f, 1.0f); }


        Quaternion operator*(const Quaternion& other) const;
        Float3 operator*(const Float3& vector) const;

        Quaternion& operator+=(const Quaternion& other) { x += other.x; y += other.y; z += other.z; w += other.w; return *this; }
        Quaternion& operator-=(const Quaternion& other) { x -= other.x; y -= other.y; z -= other.z; w -= other.w; return *this; }
        Quaternion& operator*=(const Quaternion& other) { *this = *this * other; return *this; }

        Quaternion operator+(const Quaternion& other) const { return Quaternion(*this) += other; }
        Quaternion operator-(const Quaternion& other) const { return Quaternion(*this) -= other; }

        Quaternion& operator+=(float scalar) { x += scalar; y += scalar; z += scalar; w += scalar; return *this; }
        Quaternion& operator-=(float scalar) { x -= scalar; y -= scalar; z -= scalar; w -= scalar; return *this; }
        Quaternion& operator*=(float scalar) { x *= scalar; y *= scalar; z *= scalar; w *= scalar; return *this; }
        Quaternion& operator/=(float scalar) { x /= scalar; y /= scalar; z /= scalar; w /= scalar; return *this; }

        Quaternion operator+(float scalar) const { return Quaternion(*this) += scalar; }
        Quaternion operator-(float scalar) const { return Quaternion(*this) -= scalar; }
        Quaternion operator*(float scalar) const { return Quaternion(*this) *= scalar; }
        Quaternion operator/(float scalar) const { return Quaternion(*this) /= scalar; }

        Quaternion operator+() const { return *this; }
        Quaternion operator-() const { return *this * -1.0f; }


        Bool4 operator==(const Quaternion& other) { return Bool4(x == other.x, y == other.y, z == other.z, w == other.w); }
        Bool4 operator!=(const Quaternion& other) { return Bool4(x != other.x, y != other.y, z != other.z, w != other.w); }
        Bool4 operator<=(const Quaternion& other) { return Bool4(x <= other.x, y <= other.y, z <= other.z, w <= other.w); }
        Bool4 operator< (const Quaternion& other) { return Bool4(x <  other.x, y <  other.y, z <  other.z, w <  other.w); }
        Bool4 operator>=(const Quaternion& other) { return Bool4(x >= other.x, y >= other.y, z >= other.z, w >= other.w); }
        Bool4 operator> (const Quaternion& other) { return Bool4(x >  other.x, y >  other.y, z >  other.z, w >  other.w); }


        float& operator[](std::size_t index) {
            switch(index) {
                case 0: return x;
                case 1: return y;
                case 2: return z;
                case 3: return w;
            }

            Assert(index < 4, "Invalid quaternion index: %lu", index);
            return x;
        }

        float operator[](std::size_t index) const {
            switch(index) {
                case 0: return x;
                case 1: return y;
                case 2: return z;
                case 3: return w;
            }

            Assert(index < 4, "Invalid quaternion index: %lu", index);
            return 0;
        }


        operator std::string() const {
            std::stringstream stream;
            stream << std::fixed << std::setprecision(2);
            stream << '[' << x << ", " << y << ", " << z << ", " << w << ']';
            return stream.str();
        }


        float Dot(const Quaternion& other) const { return x * other.x + y * other.y + z * other.z + w * other.w; }
        
        float Length() const { return std::sqrt(Dot(*this)); }
        Quaternion Normalize() const { return (*this) * (1.0f / Length()); }

        Quaternion Conjugate() const { return Quaternion(-x, -y, -z, w); }
        Quaternion Inverse() const { return Conjugate().Normalize(); }

        Float3 Euler() const;
        Quaternion Slerp(const Quaternion& other, float percentage) const;
    };
}
