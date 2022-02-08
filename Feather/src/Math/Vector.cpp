#include "Precompiled.hpp"

#include "Math/Matrix.hpp"
#include "Math/Vector.hpp"

using namespace std;
using namespace Feather;


Math::Vector2 operator*(const Math::Matrix2& matrix, const Math::Vector2& vector) {
    return Math::Vector2(
        matrix(0, 0) * vector.x + matrix(0, 1) * vector.y,
        matrix(1, 0) * vector.x + matrix(1, 1) * vector.y
    );
}

float Math::Cross(const Vector2& first, const Vector2& second) {
    return first.x * second.y - first.y * second.x;
}

float Math::Dot(const Vector2& first, const Vector2& second) {
    return first.x * second.x + first.y * second.y;
}


Math::Vector3 operator*(const Math::Matrix3& matrix, const Math::Vector3& vector) {
    return Math::Vector3(
        matrix(0, 0) * vector.x + matrix(0, 1) * vector.y + matrix(0, 2) * vector.z,
        matrix(1, 0) * vector.x + matrix(1, 1) * vector.y + matrix(1, 2) * vector.z,
        matrix(2, 0) * vector.x + matrix(2, 1) * vector.y + matrix(2, 2) * vector.z
    );
}

Math::Vector3 Math::Cross(const Vector3& first, const Vector3& second) {
    return Vector3(first.y * second.z - first.z * second.y, first.z * second.x - first.x * second.z, first.x * second.y - first.y * second.x);
}

float Math::Dot(const Vector3& first, const Vector3& second) {
    return first.x * second.x + first.y * second.y + first.z * second.z;
}


Math::Vector4 operator*(const Math::Matrix4& matrix, const Math::Vector4& vector) {
    return Math::Vector4(
        matrix(0, 0) * vector.x + matrix(0, 1) * vector.y + matrix(0, 2) * vector.z + matrix(0, 3) * vector.w,
        matrix(1, 0) * vector.x + matrix(1, 1) * vector.y + matrix(1, 2) * vector.z + matrix(1, 3) * vector.w,
        matrix(2, 0) * vector.x + matrix(2, 1) * vector.y + matrix(2, 2) * vector.z + matrix(2, 3) * vector.w,
        matrix(3, 0) * vector.x + matrix(3, 1) * vector.y + matrix(3, 2) * vector.z + matrix(3, 3) * vector.w
    );
}

float Math::Dot(const Vector4& first, const Vector4& second) {
    return first.x * second.x + first.y * second.y + first.z * second.z + first.w * second.w;
}
