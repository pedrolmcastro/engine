#include "Precompiled.hpp"

#include "Math/Vector.hpp"
#include "Math/Quaternion.hpp"

using namespace std;
using namespace Feather;


Math::Quaternion::Quaternion(const Float3& angles) {
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

Math::Quaternion::Quaternion(const Float3& axis, float angle) {
    Float3 normalized = axis.Normalize();
    float half = angle * 0.5f;
    float sine = sin(half);

    x = normalized.x * sine;
    y = normalized.y * sine;
    z = normalized.z * sine;
    w = cos(half);
}

Math::Quaternion::Quaternion(const Float3& first, const Float3& second) {
    Float3 cross = first.Cross(second);

    x = cross.x;
    y = cross.y;
    z = cross.z;
    w = sqrt(first.Dot(first) * second.Dot(second)) + first.Dot(second);
}


Math::Quaternion Math::Quaternion::operator*(const Quaternion& other) const {
    return Quaternion(
          x * other.w + y * other.z - z * other.y + w * other.x,
        - x * other.z + y * other.w + z * other.x + w * other.y,
          x * other.y - y * other.x + z * other.w + w * other.z,
        - x * other.x - y * other.y - z * other.z + w * other.w
    );
}

Math::Float3 Math::Quaternion::operator*(const Float3& vector) const {
    Quaternion normalized = Normalize();
    Float3 xyz(normalized.x, normalized.y, normalized.z);

    return vector + xyz.Cross(xyz.Cross(vector) + vector * normalized.w) * 2.0f;
}


Math::Float3 Math::Quaternion::Euler() const {
    Quaternion normalized = Normalize();

    float Z = atan2(2.0f * (normalized.x * normalized.w + normalized.y * normalized.z), 1.0f - 2.0f * (normalized.x * normalized.x + normalized.y * normalized.y));

    float sine = 2.0f * (normalized.y * normalized.w - normalized.x * normalized.z);
    float Y = abs(sine) >= 1 ? copysign(M_PI / 2, sine) : asin(sine);

    float X = atan2(2.0f * (normalized.x * normalized.y + normalized.z * normalized.w), 1.0f - 2.0f * (normalized.y * normalized.y + normalized.z * normalized.z));

    return Float3(Z, Y, X);
}

Math::Quaternion Math::Quaternion::Slerp(const Quaternion& other_, float percentage) const {
    Quaternion self = Normalize();
    Quaternion other = other_.Normalize();

    float dot = self.Dot(other);

    if (dot < 0.0f) {
        dot *= -1.0f;
        other *= -1.0f;
    }

    if (dot > 0.9999f) {
        other -= self;
        other *= percentage;
        return (self += other).Normalize();
    }

    float omega = acos(dot);
    float sineomega = sin(omega);
    float theta = omega * percentage;

    self *= sin(omega - theta) / sineomega;
    other *= sin(theta) / sineomega;

    return self += other;
}
