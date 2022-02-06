#pragma once


#include "Precompiled.hpp"


#define __VectorFunctions__(type)                                                                                                       \
    /* Vector Operators */                                                                                                              \
    inline type operator+(type first, const type& second) { return first += second; }                                                   \
    inline type operator-(type first, const type& second) { return first -= second; }                                                   \
    inline type operator*(type first, const type& second) { return first *= second; }                                                   \
    inline type operator/(type first, const type& second) { return first /= second; }                                                   \
    /* Scalar Operators */                                                                                                              \
    inline type operator+(type vector, float scalar) { return vector += scalar; }                                                       \
    inline type operator-(type vector, float scalar) { return vector -= scalar; }                                                       \
    inline type operator*(type vector, float scalar) { return vector *= scalar; }                                                       \
    inline type operator/(type vector, float scalar) { return vector /= scalar; }                                                       \
    /* Unary Operators */                                                                                                               \
    inline type operator-(const type& vector) { return vector * -1.0f; }                                                                \
    /* Functions */                                                                                                                     \
    inline float Norm(const type& vector) { return sqrtf(Dot(vector, vector)); }                                                        \
    inline type Normalize(const type& vector) { return vector / Norm(vector); }                                                         \
    inline float Distance(const type& first, const type& second) { return Norm(first - second); }                                       \
    inline bool Orthogonal(const type& first, const type& second) { return Dot(first, second) < 10e-6; }                                \
    inline float Angle(const type& first, const type& second) { return std::acos(Dot(first, second) / (Norm(first) * Norm(second))); }  \


// TODO: Use operator<<()
// TODO: Add Foward(), Reflect() and Refract()
namespace Feather::Math {
    class Vector2 {
    public:
        union { float x, s, u, r; };
        union { float y, t, v, g; };

        Vector2(float value = 0): x(value), y(value) {}
        Vector2(float x, float y): x(x), y(y) {}

        Vector2& operator+=(const Vector2& other) { x += other.x; y += other.y; return *this; }
        Vector2& operator-=(const Vector2& other) { x -= other.x; y -= other.y; return *this; }
        Vector2& operator*=(const Vector2& other) { x *= other.x; y *= other.y; return *this; }
        Vector2& operator/=(const Vector2& other) { x /= other.x; y /= other.y; return *this; }

        Vector2& operator+=(float scalar) { x += scalar; y += scalar; return *this; }
        Vector2& operator-=(float scalar) { x -= scalar; y -= scalar; return *this; }
        Vector2& operator*=(float scalar) { x *= scalar; y *= scalar; return *this; }
        Vector2& operator/=(float scalar) { x /= scalar; y /= scalar; return *this; }

        operator std::string() const {
            std::stringstream stream;
            stream << std::fixed << std::setprecision(2);
            stream << '[' << x << ", " << y << ']';
            return stream.str();
        }
    };

    inline float Cross(const Vector2& first, const Vector2& second) { return first.x * second.y - first.y * second.x; }
    inline float Dot(const Vector2& first, const Vector2& second) { return first.x * second.x + first.y * second.y; }
    __VectorFunctions__(Vector2);


    class Vector3 {
    public:
        union { float x, s, u, r; };
        union { float y, t, v, g; };
        union { float z, p, w, b; };

        Vector3(float value = 0): x(value), y(value), z(value) {}
        Vector3(float x, float y, float z): x(x), y(y), z(z) {}

        Vector3& operator+=(const Vector3& other) { x += other.x; y += other.y; z += other.z; return *this; }
        Vector3& operator-=(const Vector3& other) { x -= other.x; y -= other.y; z -= other.z; return *this; }
        Vector3& operator*=(const Vector3& other) { x *= other.x; y *= other.y; z *= other.z; return *this; }
        Vector3& operator/=(const Vector3& other) { x /= other.x; y /= other.y; z /= other.z; return *this; }

        Vector3& operator+=(float scalar) { x += scalar; y += scalar; z += scalar; return *this; }
        Vector3& operator-=(float scalar) { x -= scalar; y -= scalar; z -= scalar; return *this; }
        Vector3& operator*=(float scalar) { x *= scalar; y *= scalar; z *= scalar; return *this; }
        Vector3& operator/=(float scalar) { x /= scalar; y /= scalar; z /= scalar; return *this; }

        operator std::string() const {
            std::stringstream stream;
            stream << std::fixed << std::setprecision(2);
            stream << '[' << x << ", " << y << ", " << z << ']';
            return stream.str();
        }
    };

    inline Vector3 Cross(const Vector3& first, const Vector3& second) {
        return Vector3(first.y * second.z - first.z * second.y, first.z * second.x - first.x * second.z, first.x * second.y - first.y * second.x);
    }
    inline float Dot(const Vector3& first, const Vector3& second) { return first.x * second.x + first.y * second.y + first.z * second.z; }
    __VectorFunctions__(Vector3);


    class Vector4 {
    public:
        union { float x, s, r; };
        union { float y, t, g; };
        union { float z, p, b; };
        union { float w, q, a; };

        Vector4(float value = 0): x(value), y(value), z(value), w(value) {}
        Vector4(float x, float y, float z, float w): x(x), y(y), z(z), w(w) {}

        Vector4& operator+=(const Vector4& other) { x += other.x; y += other.y; z += other.z; w += other.w; return *this; }
        Vector4& operator-=(const Vector4& other) { x -= other.x; y -= other.y; z -= other.z; w -= other.w; return *this; }
        Vector4& operator*=(const Vector4& other) { x *= other.x; y *= other.y; z *= other.z; w *= other.w; return *this; }
        Vector4& operator/=(const Vector4& other) { x /= other.x; y /= other.y; z /= other.z; w /= other.w; return *this; }

        Vector4& operator+=(float scalar) { x += scalar; y += scalar; z += scalar; w += scalar; return *this; }
        Vector4& operator-=(float scalar) { x -= scalar; y -= scalar; z -= scalar; w -= scalar; return *this; }
        Vector4& operator*=(float scalar) { x *= scalar; y *= scalar; z *= scalar; w *= scalar; return *this; }
        Vector4& operator/=(float scalar) { x /= scalar; y /= scalar; z /= scalar; w /= scalar; return *this; }

        operator std::string() const {
            std::stringstream stream;
            stream << std::fixed << std::setprecision(2);
            stream << '[' << x << ", " << y << ", " << z << ", " << w << ']';
            return stream.str();
        }
    };

    inline float Dot(const Vector4& first, const Vector4& second) { return first.x * second.x + first.y * second.y + first.z * second.z + first.w * second.w; }
    __VectorFunctions__(Vector4);
}
