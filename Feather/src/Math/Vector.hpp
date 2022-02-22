#pragma once


#include "Precompiled.hpp"

#include "Math/Bool.hpp"
#include "Debug/Assert.hpp"

// TODO: Use operator<<()
namespace Feather::Math {
    template<typename T> class __Vector2__ {
    public:
        union { T x, s, u, r; };
        union { T y, t, v, g; };


        __Vector2__(T x, T y): x(x), y(y) {}
        __Vector2__(T scalar = 0): x(scalar), y(scalar) {}


        __Vector2__& operator+=(const __Vector2__& other) { x += other.x; y += other.y; return *this; }
        __Vector2__& operator-=(const __Vector2__& other) { x -= other.x; y -= other.y; return *this; }
        __Vector2__& operator*=(const __Vector2__& other) { x *= other.x; y *= other.y; return *this; }
        __Vector2__& operator/=(const __Vector2__& other) { x /= other.x; y /= other.y; return *this; }

        __Vector2__ operator+(const __Vector2__& other) const { return __Vector2__(*this) += other; }
        __Vector2__ operator-(const __Vector2__& other) const { return __Vector2__(*this) -= other; }
        __Vector2__ operator*(const __Vector2__& other) const { return __Vector2__(*this) *= other; }
        __Vector2__ operator/(const __Vector2__& other) const { return __Vector2__(*this) /= other; }

        __Vector2__& operator+=(T scalar) { x += scalar; y += scalar; return *this; }
        __Vector2__& operator-=(T scalar) { x -= scalar; y -= scalar; return *this; }
        __Vector2__& operator*=(T scalar) { x *= scalar; y *= scalar; return *this; }
        __Vector2__& operator/=(T scalar) { x /= scalar; y /= scalar; return *this; }

        __Vector2__ operator+(T scalar) const { return __Vector2__(*this) += scalar; }
        __Vector2__ operator-(T scalar) const { return __Vector2__(*this) -= scalar; }
        __Vector2__ operator*(T scalar) const { return __Vector2__(*this) *= scalar; }
        __Vector2__ operator/(T scalar) const { return __Vector2__(*this) /= scalar; }

        __Vector2__ operator+() const { return *this; }
        __Vector2__ operator-() const { return *this * -1; }


        Bool2 operator==(const __Vector2__& other) { return Bool2(x == other.x, y == other.y); }
        Bool2 operator!=(const __Vector2__& other) { return Bool2(x != other.x, y != other.y); }
        Bool2 operator<=(const __Vector2__& other) { return Bool2(x <= other.x, y <= other.y); }
        Bool2 operator< (const __Vector2__& other) { return Bool2(x <  other.x, y <  other.y); }
        Bool2 operator>=(const __Vector2__& other) { return Bool2(x >= other.x, y >= other.y); }
        Bool2 operator> (const __Vector2__& other) { return Bool2(x >  other.x, y >  other.y); }


        T& operator[](std::size_t index) {
            switch(index) {
                case 0: return x;
                case 1: return y;
            }

            Assert(index < 2, "Invalid vector index!");
            return x;
        }

        T operator[](std::size_t index) const {
            switch(index) {
                case 0: return x;
                case 1: return y;
            }

            Assert(index < 2, "Invalid vector index!");
            return 0;
        }


        operator std::string() const {
            std::stringstream stream;
            stream << std::fixed << std::setprecision(2);
            stream << '[' << x << ", " << y << ']';
            return stream.str();
        }


        T Dot(const __Vector2__& other) const { return x * other.x + y * other.y; }
        T Cross(const __Vector2__& other) const { return x * other.y - y * other.x; }

        T Length() const { return std::sqrt(Dot(*this)); }
        T Distance(const __Vector2__& other) const { return (*this - other).Length(); }
        __Vector2__ Normalize() const { T length = Length(); return length != 0 ? *this * (1 / Length()) : *this; }

        bool Orthogonal(const __Vector2__& other) const { return Dot(other) < 10e-5; }
        T Euler(const __Vector2__& other) const { return std::acos(Dot(other) / (Length() * other.Length())); }


        __Vector2__ Forward(const __Vector2__& incident, const __Vector2__& reference) { return reference.Dot(incident) < 0 ? *this : - *this; }
        __Vector2__ Reflect(const __Vector2__& normal_) const { __Vector2__ normal = normal_.Normalize(); return *this - normal * (2 * normal.Dot(*this)); }

        __Vector2__ Refract(const __Vector2__& normal_, float ratio) const {
            __Vector2__ incident = Normalize();
            __Vector2__ normal = normal_.Normalize();

            T dot = normal.Dot(incident);
            float k = 1.0f - ratio * ratio * (1.0f - dot * dot);
            return k < 0.0f ? __Vector2__() : incident * ratio - normal * (ratio * dot + std::sqrt(k));
        }
    };


    template<typename T> class __Vector3__ {
    public:
        union { T x, s, u, r; };
        union { T y, t, v, g; };
        union { T z, p, w, b; };


        __Vector3__(T x, T y, T z): x(x), y(y), z(z) {}
        __Vector3__(T scalar = 0): x(scalar), y(scalar), z(scalar) {}
        __Vector3__(const __Vector2__<T>& vector, T z = 0): x(vector.x), y(vector.y), z(z) {}


        __Vector3__& operator+=(const __Vector3__& other) { x += other.x; y += other.y; z += other.z; return *this; }
        __Vector3__& operator-=(const __Vector3__& other) { x -= other.x; y -= other.y; z -= other.z; return *this; }
        __Vector3__& operator*=(const __Vector3__& other) { x *= other.x; y *= other.y; z *= other.z; return *this; }
        __Vector3__& operator/=(const __Vector3__& other) { x /= other.x; y /= other.y; z /= other.z; return *this; }

        __Vector3__ operator+(const __Vector3__& other) const { return __Vector3__(*this) += other; }
        __Vector3__ operator-(const __Vector3__& other) const { return __Vector3__(*this) -= other; }
        __Vector3__ operator*(const __Vector3__& other) const { return __Vector3__(*this) *= other; }
        __Vector3__ operator/(const __Vector3__& other) const { return __Vector3__(*this) /= other; }

        __Vector3__& operator+=(T scalar) { x += scalar; y += scalar; z += scalar; return *this; }
        __Vector3__& operator-=(T scalar) { x -= scalar; y -= scalar; z -= scalar; return *this; }
        __Vector3__& operator*=(T scalar) { x *= scalar; y *= scalar; z *= scalar; return *this; }
        __Vector3__& operator/=(T scalar) { x /= scalar; y /= scalar; z /= scalar; return *this; }

        __Vector3__ operator+(T scalar) const { return __Vector3__(*this) += scalar; }
        __Vector3__ operator-(T scalar) const { return __Vector3__(*this) -= scalar; }
        __Vector3__ operator*(T scalar) const { return __Vector3__(*this) *= scalar; }
        __Vector3__ operator/(T scalar) const { return __Vector3__(*this) /= scalar; }

        __Vector3__ operator+() const { return *this; }
        __Vector3__ operator-() const { return *this * -1; }


        Bool3 operator==(const __Vector3__& other) { return Bool3(x == other.x, y == other.y, z == other.z); }
        Bool3 operator!=(const __Vector3__& other) { return Bool3(x != other.x, y != other.y, z != other.z); }
        Bool3 operator<=(const __Vector3__& other) { return Bool3(x <= other.x, y <= other.y, z <= other.z); }
        Bool3 operator< (const __Vector3__& other) { return Bool3(x <  other.x, y <  other.y, z <  other.z); }
        Bool3 operator>=(const __Vector3__& other) { return Bool3(x >= other.x, y >= other.y, z >= other.z); }
        Bool3 operator> (const __Vector3__& other) { return Bool3(x >  other.x, y >  other.y, z >  other.z); }


        T& operator[](std::size_t index) {
            switch(index) {
                case 0: return x;
                case 1: return y;
                case 2: return z;
            }

            Assert(index < 3, "Invalid vector index!");
            return x;
        }

        T operator[](std::size_t index) const {
            switch(index) {
                case 0: return x;
                case 1: return y;
                case 2: return z;
            }

            Assert(index < 3, "Invalid vector index!");
            return 0;
        }


        operator std::string() const {
            std::stringstream stream;
            stream << std::fixed << std::setprecision(2);
            stream << '[' << x << ", " << y << ", " << z << ']';
            return stream.str();
        }


        T Dot(const __Vector3__& other) const { return x * other.x + y * other.y + z * other.z; }
        __Vector3__ Cross(const __Vector3__& other) const { return __Vector3__(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x); }

        T Length() const { return std::sqrt(Dot(*this)); }
        T Distance(const __Vector3__& other) const { return (*this - other).Length(); }
        __Vector3__ Normalize() const { T length = Length(); return length != 0 ? *this * (1 / Length()) : *this; }

        bool Orthogonal(const __Vector3__& other) const { return Dot(other) < 10e-5; }
        T Euler(const __Vector3__& other) const { return std::acos(Dot(other) / (Length() * other.Length())); }


        __Vector3__ Forward(const __Vector3__& incident, const __Vector3__& reference) { return reference.Dot(incident) < 0 ? *this : - *this; }
        __Vector3__ Reflect(const __Vector3__& normal_) const { __Vector3__ normal = normal_.Normalize(); return *this - normal * (2 * normal.Dot(*this)); }

        __Vector3__ Refract(const __Vector3__& normal_, float ratio) const {
            __Vector3__ incident = Normalize();
            __Vector3__ normal = normal_.Normalize();

            T dot = normal.Dot(incident);
            float k = 1.0f - ratio * ratio * (1.0f - dot * dot);
            return k < 0.0f ? __Vector3__() : incident * ratio - normal * (ratio * dot + std::sqrt(k));
        }
    };


    template<typename T> class __Vector4__ {
    public:
        union { T x, s, r; };
        union { T y, t, g; };
        union { T z, p, b; };
        union { T w, q, a; };


        __Vector4__(T x, T y, T z, T w): x(x), y(y), z(z), w(w) {}
        __Vector4__(T scalar = 0): x(scalar), y(scalar), z(scalar), w(scalar) {}
        __Vector4__(const __Vector3__<T>& vector, T w = 0): x(vector.x), y(vector.y), z(vector.z), w(w) {}


        __Vector4__& operator+=(const __Vector4__& other) { x += other.x; y += other.y; z += other.z; w += other.w; return *this; }
        __Vector4__& operator-=(const __Vector4__& other) { x -= other.x; y -= other.y; z -= other.z; w -= other.w; return *this; }
        __Vector4__& operator*=(const __Vector4__& other) { x *= other.x; y *= other.y; z *= other.z; w *= other.w; return *this; }
        __Vector4__& operator/=(const __Vector4__& other) { x /= other.x; y /= other.y; z /= other.z; w /= other.w; return *this; }

        __Vector4__ operator+(const __Vector4__& other) const { return __Vector4__(*this) += other; }
        __Vector4__ operator-(const __Vector4__& other) const { return __Vector4__(*this) -= other; }
        __Vector4__ operator*(const __Vector4__& other) const { return __Vector4__(*this) *= other; }
        __Vector4__ operator/(const __Vector4__& other) const { return __Vector4__(*this) /= other; }

        __Vector4__& operator+=(T scalar) { x += scalar; y += scalar; z += scalar; w += scalar; return *this; }
        __Vector4__& operator-=(T scalar) { x -= scalar; y -= scalar; z -= scalar; w -= scalar; return *this; }
        __Vector4__& operator*=(T scalar) { x *= scalar; y *= scalar; z *= scalar; w *= scalar; return *this; }
        __Vector4__& operator/=(T scalar) { x /= scalar; y /= scalar; z /= scalar; w /= scalar; return *this; }

        __Vector4__ operator+(T scalar) const { return __Vector4__(*this) += scalar; }
        __Vector4__ operator-(T scalar) const { return __Vector4__(*this) -= scalar; }
        __Vector4__ operator*(T scalar) const { return __Vector4__(*this) *= scalar; }
        __Vector4__ operator/(T scalar) const { return __Vector4__(*this) /= scalar; }

        __Vector4__ operator+() const { return *this; }
        __Vector4__ operator-() const { return *this * -1; }


        Bool4 operator==(const __Vector4__& other) { return Bool4(x == other.x, y == other.y, z == other.z, w == other.w); }
        Bool4 operator!=(const __Vector4__& other) { return Bool4(x != other.x, y != other.y, z != other.z, w != other.w); }
        Bool4 operator<=(const __Vector4__& other) { return Bool4(x <= other.x, y <= other.y, z <= other.z, w <= other.w); }
        Bool4 operator< (const __Vector4__& other) { return Bool4(x <  other.x, y <  other.y, z <  other.z, w <  other.w); }
        Bool4 operator>=(const __Vector4__& other) { return Bool4(x >= other.x, y >= other.y, z >= other.z, w >= other.w); }
        Bool4 operator> (const __Vector4__& other) { return Bool4(x >  other.x, y >  other.y, z >  other.z, w >  other.w); }


        T& operator[](std::size_t index) {
            switch(index) {
                case 0: return x;
                case 1: return y;
                case 2: return z;
                case 3: return w;
            }

            Assert(index < 4, "Invalid vector index!");
            return x;
        }

        T operator[](std::size_t index) const {
            switch(index) {
                case 0: return x;
                case 1: return y;
                case 2: return z;
                case 3: return w;
            }

            Assert(index < 4, "Invalid vector index!");
            return 0;
        }


        operator std::string() const {
            std::stringstream stream;
            stream << std::fixed << std::setprecision(2);
            stream << '[' << x << ", " << y << ", " << z << ", " << w << ']';
            return stream.str();
        }


        T Dot(const __Vector4__& other) const { return x * other.x + y * other.y + z * other.z + w * other.w; }

        T Length() const { return std::sqrt(Dot(*this)); }
        T Distance(const __Vector4__& other) const { return (*this - other).Length(); }
        __Vector4__ Normalize() const { T length = Length(); return length != 0 ? *this * (1 / Length()) : *this; }

        bool Orthogonal(const __Vector4__& other) const { return Dot(other) < 10e-5; }
        T Euler(const __Vector4__& other) const { return std::acos(Dot(other) / (Length() * other.Length())); }


        __Vector4__ Forward(const __Vector4__& incident, const __Vector4__& reference) { return reference.Dot(incident) < 0 ? *this : - *this; }
        __Vector4__ Reflect(const __Vector4__& normal_) const { __Vector4__ normal = normal_.Normalize(); return *this - normal * (2 * normal.Dot(*this)); }

        __Vector4__ Refract(const __Vector4__& normal_, float ratio) const {
            __Vector4__ incident = Normalize();
            __Vector4__ normal = normal_.Normalize();

            T dot = normal.Dot(incident);
            float k = 1.0f - ratio * ratio * (1.0f - dot * dot);
            return k < 0.0f ? __Vector4__() : incident * ratio - normal * (ratio * dot + std::sqrt(k));
        }
    };


    using Int2 = __Vector2__<int>;
    using Int3 = __Vector3__<int>;
    using Int4 = __Vector4__<int>;

    using Float2 = __Vector2__<float>;
    using Float3 = __Vector3__<float>;
    using Float4 = __Vector4__<float>;

    using Double2 = __Vector2__<double>;
    using Double3 = __Vector3__<double>;
    using Double4 = __Vector4__<double>;

    using Unsigned2 = __Vector2__<unsigned>;
    using Unsigned3 = __Vector3__<unsigned>;
    using Unsigned4 = __Vector4__<unsigned>;
}
