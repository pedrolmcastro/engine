#include "Precompiled.hpp"

#include "Math/Vector.hpp"
#include "Math/Quaternion.hpp"

using namespace std;
using namespace Feather;


Math::Quaternion::Quaternion(const Vector3& angles) {
    float Z = angles.x * 0.5f;
    float Y = angles.y * 0.5f;
    float X = angles.z * 0.5f;

    float sinX = sin(X);
    float cosX = cos(X);
    float sinY = sin(Y);
    float cosY = cos(Y);
    float sinZ = sin(Z);
    float cosZ = cos(Z);

    x = sinZ * cosY * cosX - cosZ * sinY * sinX;
    y = cosZ * sinY * cosX + sinZ * cosY * sinX;
    z = cosZ * cosY * sinX - sinZ * sinY * cosX;
    w = cosZ * cosY * cosX + sinZ * sinY * sinX;
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
}

Math::Quaternion Math::operator*(const Quaternion& first, const Quaternion& second) {
    return Quaternion(
          first.x * second.w + first.y * second.z - first.z * second.y + first.w * second.x,
        - first.x * second.z + first.y * second.w + first.z * second.x + first.w * second.y,
          first.x * second.y - first.y * second.x + first.z * second.w + first.w * second.z,
        - first.x * second.x - first.y * second.y - first.z * second.z + first.w * second.w
    );
}

Math::Vector3 Math::operator*(const Quaternion& quaternion, const Vector3& vector) {
    Quaternion normalized = Normalize(quaternion);
    Vector3 xyz(normalized.x, normalized.y, normalized.z);

    return vector + Cross(xyz, Cross(xyz, vector) + vector * normalized.w) * 2.0f;
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


Math::Vector3 Math::Euler(const Quaternion& quaternion) {
    Quaternion normalized = Normalize(quaternion);

    float Z = atan2(2.0f * (normalized.x * normalized.w + normalized.y * normalized.z), 1.0f - 2.0f * (normalized.x * normalized.x + normalized.y * normalized.y));

    float sine = 2.0f * (normalized.y * normalized.w - normalized.x * normalized.z);
    float Y = abs(sine) >= 1 ? copysign(M_PI / 2, sine) : asin(sine);

    float X = atan2(2.0f * (normalized.x * normalized.y + normalized.z * normalized.w), 1.0f - 2.0f * (normalized.y * normalized.y + normalized.z * normalized.z));

    return Vector3(Z, Y, X);
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
