#pragma once


#include "Math/Vector.hpp"

// TODO: Use operator<<()
namespace Feather::Math {
    class Quaternion {
    public:
        float x, y, z, w;

        Quaternion(const Vector3& angles);
        Quaternion(const Vector3& axis, float angle);
        Quaternion(const Vector3& first, const Vector3& second);
        Quaternion(float x, float y, float z, float w): x(x), y(y), z(z), w(w) {}
        Quaternion(float scalar = 0.0f): x(scalar), y(scalar), z(scalar), w(scalar) {}

        static Quaternion Identity() { return Quaternion(0.0f, 0.0f, 0.0f, 1.0f); }

        friend Quaternion operator*(const Quaternion& first, const Quaternion& second);
        Quaternion& operator*=(const Quaternion& other) { *this = *this * other; return *this; };

        Quaternion& operator+=(const Quaternion& other) { x += other.x; y += other.y; z += other.z; w += other.w; return *this; }
        Quaternion& operator-=(const Quaternion& other) { x -= other.x; y -= other.y; z -= other.z; w -= other.w; return *this; }

        Quaternion& operator+=(float scalar) { x += scalar; y += scalar; z += scalar; w += scalar; return *this; }
        Quaternion& operator-=(float scalar) { x -= scalar; y -= scalar; z -= scalar; w -= scalar; return *this; }
        Quaternion& operator*=(float scalar) { x *= scalar; y *= scalar; z *= scalar; w *= scalar; return *this; }
        Quaternion& operator/=(float scalar) { x /= scalar; y /= scalar; z /= scalar; w /= scalar; return *this; }

        operator std::string() const {
            std::stringstream stream;
            stream << std::fixed << std::setprecision(2);
            stream << '[' << x << ", " << y << ", " << z << ", " << w << ']';
            return stream.str();
        }
    };


    float Norm(const Quaternion& quaternion);
    Quaternion Normalize(const Quaternion& quaternion);
    float Dot(const Quaternion& first, const Quaternion& second);

    Quaternion Inverse(const Quaternion& quaternion);
    Quaternion Conjugate(const Quaternion& quaternion);

    Vector3 Euler(const Quaternion& quaternion);
    Quaternion Slerp(const Quaternion& first, const Quaternion& second, float percentage);


    Quaternion operator*(const Quaternion& first, const Quaternion& second);
    Vector3 operator*(const Quaternion& quaternion, const Vector3& vector);

    inline Quaternion operator+(Quaternion first, const Quaternion& second) { return first += second; }
    inline Quaternion operator-(Quaternion first, const Quaternion& second) { return first -= second; }

    inline Quaternion operator+(Quaternion quaternion, float scalar) { return quaternion += scalar; }
    inline Quaternion operator-(Quaternion quaternion, float scalar) { return quaternion -= scalar; }
    inline Quaternion operator*(Quaternion quaternion, float scalar) { return quaternion *= scalar; }
    inline Quaternion operator/(Quaternion quaternion, float scalar) { return quaternion /= scalar; }

    inline Quaternion operator-(const Quaternion& quaternion) { return quaternion * -1.0f; }
}
