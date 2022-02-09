#include "Precompiled.hpp"

#include "Math/Matrix.hpp"
#include "Math/Vector.hpp"
#include "Math/Quaternion.hpp"

using namespace std;
using namespace Feather;


Math::Matrix2::Matrix2(float diagonal) {
    elements.fill(0.0f);

    (*this)(0, 0) = diagonal;
    (*this)(1, 1) = diagonal;
}

Math::Matrix2 Math::operator*(const Matrix2& first, const Matrix2& second) {
    Matrix2 product;

    for (size_t i = 0; i < 2; i++) {
        for (size_t j = 0; j < 2; j++) {
            product(i, j) = 0.0f;
            for (size_t k = 0; k < 2; k++) product(i, j) += first(i, k) * second(k, j);
        }
    }

    return product;
}

Math::Vector2 Math::operator*(const Matrix2& matrix, const Vector2& vector) {
    return Vector2(
        matrix(0, 0) * vector.x + matrix(0, 1) * vector.y,
        matrix(1, 0) * vector.x + matrix(1, 1) * vector.y
    );
}

Math::Matrix2 Math::Inverse(const Matrix2& matrix) {
    Matrix2 inverse;

    inverse(0, 0) =   matrix(1, 1);
    inverse(0, 1) = - matrix(0, 1);
    inverse(1, 0) = - matrix(1, 0);
    inverse(1, 1) =   matrix(1, 0);

    return inverse *= 1.0f / Determinant(matrix);
}

Math::Matrix2 Math::Transpose(const Matrix2& matrix) {
    Matrix2 transpose(matrix);

    transpose(0, 1) = matrix(1, 0);
    transpose(1, 0) = matrix(0, 1);

    return transpose;
}

float Math::Determinant(const Matrix2& matrix) {
    return matrix(0, 0) * matrix(1, 1) - matrix(0, 1) * matrix(1, 0);
}


Math::Matrix3::Matrix3(float diagonal) {
    elements.fill(0.0f);

    (*this)(0, 0) = diagonal;
    (*this)(1, 1) = diagonal;
    (*this)(2, 2) = diagonal;
}

Math::Matrix3 Math::operator*(const Matrix3& first, const Matrix3& second) {
    Matrix3 product;

    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++) {
            product(i, j) = 0.0f;
            for (size_t k = 0; k < 3; k++) product(i, j) += first(i, k) * second(k, j);
        }
    }

    return product;
}

Math::Vector3 Math::operator*(const Matrix3& matrix, const Vector3& vector) {
    return Vector3(
        matrix(0, 0) * vector.x + matrix(0, 1) * vector.y + matrix(0, 2) * vector.z,
        matrix(1, 0) * vector.x + matrix(1, 1) * vector.y + matrix(1, 2) * vector.z,
        matrix(2, 0) * vector.x + matrix(2, 1) * vector.y + matrix(2, 2) * vector.z
    );
}

Math::Matrix3 Math::Inverse(const Matrix3& matrix) {
    Matrix3 inverse;

    inverse(0, 0) = matrix(1, 1) * matrix(2, 2) - matrix(2, 1) * matrix(1, 2);
    inverse(0, 1) = matrix(0, 2) * matrix(2, 1) - matrix(0, 1) * matrix(2, 2);
    inverse(0, 2) = matrix(0, 1) * matrix(1, 2) - matrix(0, 2) * matrix(1, 1);
    inverse(1, 0) = matrix(1, 2) * matrix(2, 0) - matrix(1, 0) * matrix(2, 2);
    inverse(1, 1) = matrix(0, 0) * matrix(2, 2) - matrix(0, 2) * matrix(2, 0);
    inverse(1, 2) = matrix(1, 0) * matrix(0, 2) - matrix(0, 0) * matrix(1, 2);
    inverse(2, 0) = matrix(1, 0) * matrix(2, 1) - matrix(2, 0) * matrix(1, 1);
    inverse(2, 1) = matrix(2, 0) * matrix(0, 1) - matrix(0, 0) * matrix(2, 1);
    inverse(2, 2) = matrix(0, 0) * matrix(1, 1) - matrix(1, 0) * matrix(0, 1);

    return inverse *= 1.0f / Determinant(matrix);
}

Math::Matrix3 Math::Transpose(const Matrix3& matrix) {
    Matrix3 transpose(matrix);

    transpose(0, 1) = matrix(1, 0);
    transpose(0, 2) = matrix(2, 0);

    transpose(1, 0) = matrix(0, 1);
    transpose(1, 2) = matrix(2, 1);

    transpose(2, 0) = matrix(0, 2);
    transpose(2, 1) = matrix(1, 2);

    return transpose;
}

float Math::Determinant(const Matrix3& matrix) {
    return (
        matrix(0, 0) * (matrix(1, 1) * matrix(2, 2) - matrix(2, 1) * matrix(1, 2)) -
        matrix(0, 1) * (matrix(1, 0) * matrix(2, 2) - matrix(1, 2) * matrix(2, 0)) +
        matrix(0, 2) * (matrix(1, 0) * matrix(2, 1) - matrix(1, 1) * matrix(2, 0))
    );
}


Math::Matrix4::Matrix4(float diagonal) {
    elements.fill(0.0f);

    (*this)(0, 0) = diagonal;
    (*this)(1, 1) = diagonal;
    (*this)(2, 2) = diagonal;
    (*this)(3, 3) = diagonal;
}

Math::Matrix4 Math::operator*(const Matrix4& first, const Matrix4& second) {
    Matrix4 product;

    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 4; j++) {
            product(i, j) = 0.0f;
            for (size_t k = 0; k < 4; k++) product(i, j) += first(i, k) * second(k, j);
        }
    }

    return product;
}

Math::Vector4 Math::operator*(const Matrix4& matrix, const Vector4& vector) {
    return Vector4(
        matrix(0, 0) * vector.x + matrix(0, 1) * vector.y + matrix(0, 2) * vector.z + matrix(0, 3) * vector.w,
        matrix(1, 0) * vector.x + matrix(1, 1) * vector.y + matrix(1, 2) * vector.z + matrix(1, 3) * vector.w,
        matrix(2, 0) * vector.x + matrix(2, 1) * vector.y + matrix(2, 2) * vector.z + matrix(2, 3) * vector.w,
        matrix(3, 0) * vector.x + matrix(3, 1) * vector.y + matrix(3, 2) * vector.z + matrix(3, 3) * vector.w
    );
}

Math::Matrix4 Math::Inverse(const Matrix4& matrix) {
    Matrix4 inverse;

    inverse(0, 0) = (
        matrix(1, 1) * matrix(2, 2) * matrix(3, 3) -
        matrix(1, 1) * matrix(3, 2) * matrix(2, 3) -
        matrix(1, 2) * matrix(2, 1) * matrix(3, 3) +
        matrix(1, 2) * matrix(3, 1) * matrix(2, 3) +
        matrix(1, 3) * matrix(2, 1) * matrix(3, 2) -
        matrix(1, 3) * matrix(3, 1) * matrix(2, 2)
    );

    inverse(0, 1) = (
        - matrix(0, 1) * matrix(2, 2) * matrix(3, 3) +
          matrix(0, 1) * matrix(3, 2) * matrix(2, 3) +
          matrix(0, 2) * matrix(2, 1) * matrix(3, 3) -
          matrix(0, 2) * matrix(3, 1) * matrix(2, 3) -
          matrix(0, 3) * matrix(2, 1) * matrix(3, 2) +
          matrix(0, 3) * matrix(3, 1) * matrix(2, 2)
    );

    inverse(0, 2) = (
        matrix(0, 1) * matrix(1, 2) * matrix(3, 3) -
        matrix(0, 1) * matrix(3, 2) * matrix(1, 3) -
        matrix(0, 2) * matrix(1, 1) * matrix(3, 3) +
        matrix(0, 2) * matrix(3, 1) * matrix(1, 3) +
        matrix(0, 3) * matrix(1, 1) * matrix(3, 2) -
        matrix(0, 3) * matrix(3, 1) * matrix(1, 2)
    );

    inverse(0, 3) = (
        - matrix(0, 1) * matrix(1, 2) * matrix(2, 3) +
          matrix(0, 1) * matrix(2, 2) * matrix(1, 3) +
          matrix(0, 2) * matrix(1, 1) * matrix(2, 3) -
          matrix(0, 2) * matrix(2, 1) * matrix(1, 3) -
          matrix(0, 3) * matrix(1, 1) * matrix(2, 2) +
          matrix(0, 3) * matrix(2, 1) * matrix(1, 2)
    );

    inverse(1, 0) = (
        - matrix(1, 0) * matrix(2, 2) * matrix(3, 3) +
          matrix(1, 0) * matrix(3, 2) * matrix(2, 3) +
          matrix(1, 2) * matrix(2, 0) * matrix(3, 3) -
          matrix(1, 2) * matrix(3, 0) * matrix(2, 3) -
          matrix(1, 3) * matrix(2, 0) * matrix(3, 2) +
          matrix(1, 3) * matrix(3, 0) * matrix(2, 2)
    );

    inverse(1, 1) = (
        matrix(0, 0) * matrix(2, 2) * matrix(3, 3) -
        matrix(0, 0) * matrix(3, 2) * matrix(2, 3) -
        matrix(0, 2) * matrix(2, 0) * matrix(3, 3) +
        matrix(0, 2) * matrix(3, 0) * matrix(2, 3) +
        matrix(0, 3) * matrix(2, 0) * matrix(3, 2) -
        matrix(0, 3) * matrix(3, 0) * matrix(2, 2)
    );

    inverse(1, 2) = (
        - matrix(0, 0) * matrix(1, 2) * matrix(3, 3) +
          matrix(0, 0) * matrix(3, 2) * matrix(1, 3) +
          matrix(0, 2) * matrix(1, 0) * matrix(3, 3) -
          matrix(0, 2) * matrix(3, 0) * matrix(1, 3) -
          matrix(0, 3) * matrix(1, 0) * matrix(3, 2) +
          matrix(0, 3) * matrix(3, 0) * matrix(1, 2)
    );

    inverse(1, 3) = (
        matrix(0, 0) * matrix(1, 2) * matrix(2, 3) -
        matrix(0, 0) * matrix(2, 2) * matrix(1, 3) -
        matrix(0, 2) * matrix(1, 0) * matrix(2, 3) +
        matrix(0, 2) * matrix(2, 0) * matrix(1, 3) +
        matrix(0, 3) * matrix(1, 0) * matrix(2, 2) -
        matrix(0, 3) * matrix(2, 0) * matrix(1, 2)
    );

    inverse(2, 0) = (
        matrix(1, 0) * matrix(2, 1) * matrix(3, 3) -
        matrix(1, 0) * matrix(3, 1) * matrix(2, 3) -
        matrix(1, 1) * matrix(2, 0) * matrix(3, 3) +
        matrix(1, 1) * matrix(3, 0) * matrix(2, 3) +
        matrix(1, 3) * matrix(2, 0) * matrix(3, 1) -
        matrix(1, 3) * matrix(3, 0) * matrix(2, 1)
    );

    inverse(2, 1) = (
        - matrix(0, 0) * matrix(2, 1) * matrix(3, 3) +
          matrix(0, 0) * matrix(3, 1) * matrix(2, 3) +
          matrix(0, 1) * matrix(2, 0) * matrix(3, 3) -
          matrix(0, 1) * matrix(3, 0) * matrix(2, 3) -
          matrix(0, 3) * matrix(2, 0) * matrix(3, 1) +
          matrix(0, 3) * matrix(3, 0) * matrix(2, 1)
    );

    inverse(2, 2) = (
        matrix(0, 0) * matrix(1, 1) * matrix(3, 3) -
        matrix(0, 0) * matrix(3, 1) * matrix(1, 3) -
        matrix(0, 1) * matrix(1, 0) * matrix(3, 3) +
        matrix(0, 1) * matrix(3, 0) * matrix(1, 3) +
        matrix(0, 3) * matrix(1, 0) * matrix(3, 1) -
        matrix(0, 3) * matrix(3, 0) * matrix(1, 1)
    );

    inverse(2, 3) = (
        - matrix(0, 0) * matrix(1, 1) * matrix(2, 3) +
          matrix(0, 0) * matrix(2, 1) * matrix(1, 3) +
          matrix(0, 1) * matrix(1, 0) * matrix(2, 3) -
          matrix(0, 1) * matrix(2, 0) * matrix(1, 3) -
          matrix(0, 3) * matrix(1, 0) * matrix(2, 1) +
          matrix(0, 3) * matrix(2, 0) * matrix(1, 1)
    );

    inverse(3, 0) = (
        - matrix(1, 0) * matrix(2, 1) * matrix(3, 2) +
          matrix(1, 0) * matrix(3, 1) * matrix(2, 2) +
          matrix(1, 1) * matrix(2, 0) * matrix(3, 2) -
          matrix(1, 1) * matrix(3, 0) * matrix(2, 2) -
          matrix(1, 2) * matrix(2, 0) * matrix(3, 1) +
          matrix(1, 2) * matrix(3, 0) * matrix(2, 1)
    );

    inverse(3, 1) = (
        matrix(0, 0) * matrix(2, 1) * matrix(3, 2) -
        matrix(0, 0) * matrix(3, 1) * matrix(2, 2) -
        matrix(0, 1) * matrix(2, 0) * matrix(3, 2) +
        matrix(0, 1) * matrix(3, 0) * matrix(2, 2) +
        matrix(0, 2) * matrix(2, 0) * matrix(3, 1) -
        matrix(0, 2) * matrix(3, 0) * matrix(2, 1)
    );

    inverse(3, 2) = (
        - matrix(0, 0) * matrix(1, 1) * matrix(3, 2) +
          matrix(0, 0) * matrix(3, 1) * matrix(1, 2) +
          matrix(0, 1) * matrix(1, 0) * matrix(3, 2) -
          matrix(0, 1) * matrix(3, 0) * matrix(1, 2) -
          matrix(0, 2) * matrix(1, 0) * matrix(3, 1) +
          matrix(0, 2) * matrix(3, 0) * matrix(1, 1)
    );

    inverse(3, 3) = (
        matrix(0, 0) * matrix(1, 1) * matrix(2, 2) -
        matrix(0, 0) * matrix(2, 1) * matrix(1, 2) -
        matrix(0, 1) * matrix(1, 0) * matrix(2, 2) +
        matrix(0, 1) * matrix(2, 0) * matrix(1, 2) +
        matrix(0, 2) * matrix(1, 0) * matrix(2, 1) -
        matrix(0, 2) * matrix(2, 0) * matrix(1, 1)
    );

    float determinant = matrix(0, 0) * inverse(0, 0) + matrix(1, 0) * inverse(0, 1) + matrix(2, 0) * inverse(0, 2) + matrix(3, 0) * inverse(0, 3);
    return inverse *= 1.0f / determinant;
}

Math::Matrix4 Math::Transpose(const Matrix4& matrix) {
    Matrix4 transpose(matrix);

    transpose(0, 1) = matrix(1, 0);
    transpose(0, 2) = matrix(2, 0);
    transpose(0, 3) = matrix(3, 0);

    transpose(1, 0) = matrix(0, 1);
    transpose(1, 2) = matrix(2, 1);
    transpose(1, 3) = matrix(3, 1);

    transpose(2, 0) = matrix(0, 2);
    transpose(2, 1) = matrix(1, 2);
    transpose(2, 3) = matrix(3, 2);

    transpose(3, 0) = matrix(0, 3);
    transpose(3, 1) = matrix(1, 3);
    transpose(3, 2) = matrix(2, 3);

    return transpose;
}

float Math::Determinant(const Matrix4& matrix) {
    return (
        matrix(0, 3) * matrix(1, 2) * matrix(2, 1) * matrix(3, 0) - matrix(0, 2) * matrix(1, 3) * matrix(2, 1) * matrix(3, 0) -
        matrix(0, 3) * matrix(1, 1) * matrix(2, 2) * matrix(3, 0) + matrix(0, 1) * matrix(1, 3) * matrix(2, 2) * matrix(3, 0) +
        matrix(0, 2) * matrix(1, 1) * matrix(2, 3) * matrix(3, 0) - matrix(0, 1) * matrix(1, 2) * matrix(2, 3) * matrix(3, 0) -
        matrix(0, 3) * matrix(1, 2) * matrix(2, 0) * matrix(3, 1) + matrix(0, 2) * matrix(1, 3) * matrix(2, 0) * matrix(3, 1) +
        matrix(0, 3) * matrix(1, 0) * matrix(2, 2) * matrix(3, 1) - matrix(0, 0) * matrix(1, 3) * matrix(2, 2) * matrix(3, 1) -
        matrix(0, 2) * matrix(1, 0) * matrix(2, 3) * matrix(3, 1) + matrix(0, 0) * matrix(1, 2) * matrix(2, 3) * matrix(3, 1) +
        matrix(0, 3) * matrix(1, 1) * matrix(2, 0) * matrix(3, 2) - matrix(0, 1) * matrix(1, 3) * matrix(2, 0) * matrix(3, 2) -
        matrix(0, 3) * matrix(1, 0) * matrix(2, 1) * matrix(3, 2) + matrix(0, 0) * matrix(1, 3) * matrix(2, 1) * matrix(3, 2) +
        matrix(0, 1) * matrix(1, 0) * matrix(2, 3) * matrix(3, 2) - matrix(0, 0) * matrix(1, 1) * matrix(2, 3) * matrix(3, 2) -
        matrix(0, 2) * matrix(1, 1) * matrix(2, 0) * matrix(3, 3) + matrix(0, 1) * matrix(1, 2) * matrix(2, 0) * matrix(3, 3) +
        matrix(0, 2) * matrix(1, 0) * matrix(2, 1) * matrix(3, 3) - matrix(0, 0) * matrix(1, 2) * matrix(2, 1) * matrix(3, 3) -
        matrix(0, 1) * matrix(1, 0) * matrix(2, 2) * matrix(3, 3) + matrix(0, 0) * matrix(1, 1) * matrix(2, 2) * matrix(3, 3)
    );
}


Math::Matrix4 Math::Scale(const Vector3& scale) {
    Matrix4 matrix(1.0f);

    matrix(0, 0) = scale.x;
    matrix(1, 1) = scale.y;
    matrix(2, 2) = scale.z;

    return matrix;
}

Math::Matrix4 Math::Translate(const Vector3& translation) {
    Matrix4 matrix(1.0f);

    matrix(0, 3) = translation.x;
    matrix(1, 3) = translation.y;
    matrix(2, 3) = translation.z;

    return matrix;
}

Math::Matrix4 Math::Rotate(const Vector3& axis, float angle) {
    Matrix4 rotation(1.0f);

    float sine = sin(angle);
    float cosine = cos(angle);

    Vector3 normalized = Normalize(axis);
    Vector3 auxiliar = normalized * (1.0f - cosine);

    rotation(0, 0) = auxiliar.x * normalized.x + cosine;
    rotation(1, 0) = auxiliar.x * normalized.y + normalized.z * sine;
    rotation(2, 0) = auxiliar.x * normalized.z - normalized.y * sine;

    rotation(0, 1) = auxiliar.y * normalized.x - normalized.z * sine;
    rotation(1, 1) = auxiliar.y * normalized.y + cosine;
    rotation(2, 1) = auxiliar.y * normalized.z + normalized.x * sine;

    rotation(0, 2) = auxiliar.z * normalized.x + normalized.y * sine;
    rotation(1, 2) = auxiliar.z * normalized.y - normalized.x * sine;
    rotation(2, 2) = auxiliar.z * normalized.z + cosine;

    return rotation;
}

Math::Matrix4 Math::Rotate(const Quaternion& quaternion) {
    Matrix4 rotation(1.0f);
    Quaternion normalized = Normalize(quaternion);

    rotation(0, 0) = 1.0f - 2.0f * (normalized.y * normalized.y + normalized.z * normalized.z);
    rotation(1, 0) = 2.0f * (normalized.x * normalized.y + normalized.z * normalized.w);
    rotation(2, 0) = 2.0f * (normalized.x * normalized.z - normalized.y * normalized.w);

    rotation(0, 1) = 2.0f * (normalized.x * normalized.y - normalized.z * normalized.w);
    rotation(1, 1) = 1.0f - 2.0f * (normalized.x * normalized.x + normalized.z * normalized.z);
    rotation(2, 1) = 2.0f * (normalized.y * normalized.z + normalized.x * normalized.w);

    rotation(0, 2) = 2.0f * (normalized.x * normalized.z + normalized.y * normalized.w);
    rotation(1, 2) = 2.0f * (normalized.y * normalized.z - normalized.x * normalized.w);
    rotation(2, 2) = 1.0f - 2.0f * (normalized.x * normalized.x + normalized.y * normalized.y);

    return rotation;
}


Math::Matrix4 Math::Perspective(float fov, float aspect, float near, float far) {
    Matrix4 perspective;
    float tangent = tan(fov * 0.5f);

    perspective(0, 0) = 1.0f / (aspect * tangent);
    perspective(1, 1) = 1.0f / tangent;
    perspective(2, 2) = - (far + near) / (far - near);
    perspective(3, 2) = - 1.0f;
    perspective(2, 3) = - (2.0f * far * near) / (far - near);

    return perspective;
}

Math::Matrix4 Math::Orthographic(float left, float right, float bottom, float top, float near, float far) {
    Matrix4 orthographic(1.0f);

    float width  = (right - left);
    float height = (top - bottom);
    float clip   = (far - near);

    orthographic(0, 0) = 2.0f / width;
    orthographic(1, 1) = 2.0f / height;
    orthographic(2, 2) = - 2.0f / clip;

    orthographic(0, 3) = - (right + left) / width;
    orthographic(1, 3) = - (top + bottom) / height;
    orthographic(2, 3) = - (far + near) / clip;

    return orthographic;
}

Math::Matrix4 Math::Look(const Vector3& position, const Vector3& target, const Vector3& up) {
    Matrix4 look(1.0f);

    Vector3 zaxis(Normalize(target - position));
    Vector3 xaxis(Normalize(Cross(zaxis, up)));
    Vector3 yaxis(Cross(xaxis, zaxis));

    look(0, 0) = xaxis.x;
    look(0, 1) = xaxis.y;
    look(0, 2) = xaxis.z;
    look(0, 3) = - Dot(xaxis, position);

    look(1, 0) = yaxis.x;
    look(1, 1) = yaxis.y;
    look(1, 2) = yaxis.z;
    look(1, 3) = - Dot(yaxis, position);

    look(2, 0) = - zaxis.x;
    look(2, 1) = - zaxis.y;
    look(2, 2) = - zaxis.z;
    look(2, 3) = Dot(zaxis, position);

    return look;
}
