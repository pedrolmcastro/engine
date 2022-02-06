#include "Precompiled.hpp"

#include "Math/Vector.hpp"

using namespace std;
using namespace Feather;


float Math::Cross(const Vector2& first, const Vector2& second) {
    return first.x * second.y - first.y * second.x;
}

float Math::Dot(const Vector2& first, const Vector2& second) {
    return first.x * second.x + first.y * second.y;
}


Math::Vector3 Math::Cross(const Vector3& first, const Vector3& second) {
    return Vector3(first.y * second.z - first.z * second.y, first.z * second.x - first.x * second.z, first.x * second.y - first.y * second.x);
}

float Math::Dot(const Vector3& first, const Vector3& second) {
    return first.x * second.x + first.y * second.y + first.z * second.z;
}


float Math::Dot(const Vector4& first, const Vector4& second) {
    return first.x * second.x + first.y * second.y + first.z * second.z + first.w * second.w;
}
