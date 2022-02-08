#include "Precompiled.hpp"

#include "Math/Vector.hpp"
#include "Math/Quaternion.hpp"

using namespace std;
using namespace Feather;


Math::Quaternion::Quaternion(const Vector3& angles) {
    Quaternion pitch = { 1.0f, 0.0f, 0.0f, angles.x };
	Quaternion yaw   = { 0.0f, 1.0f, 0.0f, angles.y };
	Quaternion roll  = { 0.0f, 0.0f, 1.0f, angles.z };

    *this = pitch * yaw * roll;
}

Math::Quaternion::Quaternion(const Vector3& axis, float angle) {
    Vector3 normalized = Normalize(axis);
    float half = angle * 0.5f;
    float sine = sin(half);

    x = normalized.x * sine;
    y = normalized.y * sine;
    z = normalized.z * sine;
    w = cos(half);
}

Math::Quaternion::Quaternion(const Vector3& first, const Vector3& second) {
    Vector3 cross = Cross(first, second);

    x = cross.x;
    y = cross.y;
    z = cross.z;
    w = sqrt(Dot(first, first) * Dot(second, second)) + Dot(first, second);

    (*this) = Normalize(*this);
}

Math::Quaternion operator*(const Math::Quaternion& first, const Math::Quaternion& second) {
    return Math::Normalize(Math::Quaternion(
          first.x * second.w + first.y * second.z - first.z * second.y + first.w * second.x,
        - first.x * second.z + first.y * second.w + first.z * second.x + first.w * second.y,
          first.x * second.y - first.y * second.x + first.z * second.w + first.w * second.z,
        - first.x * second.x - first.y * second.y - first.z * second.z + first.w * second.w
    ));
}


float Math::Norm(const Quaternion& quaternion) {
    return sqrt(Dot(quaternion, quaternion));
}

Math::Quaternion Math::Normalize(const Quaternion& quaternion) {
    return quaternion * (1.0f / Norm(quaternion));
}

float Math::Dot(const Quaternion& first, const Quaternion& second) {
    return first.x * second.x + first.y * second.y + first.z * second.z + first.w * second.w;
}


Math::Quaternion Math::Inverse(const Quaternion& quaternion) {
    return Normalize(Conjugate(quaternion));
}

Math::Quaternion Math::Conjugate(const Quaternion& quaternion) {
    return Quaternion(- quaternion.x, - quaternion.y, - quaternion.z, quaternion.w);
}


Math::Vector3 Math::Euler(const Quaternion& quaterion) {
    return Vector3(
        atan2(2.0f * quaterion.x * quaterion.w - 2.0f * quaterion.y * quaterion.z, 1.0f - 2.0f * quaterion.x * quaterion.x - 2.0f * quaterion.z * quaterion.z),
        atan2(2.0f * quaterion.y * quaterion.w - 2.0f * quaterion.x * quaterion.z, 1.0f - 2.0f * quaterion.y * quaterion.y - 2.0f * quaterion.z * quaterion.z),
        asin(2.0f * quaterion.x * quaterion.y + 2.0f * quaterion.z * quaterion.w)
    );
}

Math::Quaternion Math::Slerp(const Quaternion& first_, const Quaternion& second_, float percentage) {
    Quaternion first = Normalize(first_);
    Quaternion second = Normalize(second_);

    float dot = Dot(first, second);

    if (dot < 0.0f) {
        dot *= -1.0f;
        second *= -1.0f;
    }

    if (dot > 0.9999f) {
        second -= first;
        second *= percentage;
        return Normalize(first += second);
    }

    float omega = acos(dot);
    float sineomega = sin(omega);
    float theta = omega * percentage;

    first *= sin(omega - theta) / sineomega;
    second *= sin(theta) / sineomega;

    return first += second;
}
