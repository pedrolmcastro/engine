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

Math::Matrix2 Math::Matrix2::Fill(float scalar) {
    Matrix2 matrix;
    matrix.elements.fill(scalar);

    return matrix;
}

Math::Matrix2 Math::Matrix2::operator*(const Matrix2& other) const {
    Matrix2 product;

    for (size_t i = 0; i < 2; i++) {
        for (size_t j = 0; j < 2; j++) {
            for (size_t k = 0; k < 2; k++) product(i, j) += (*this)(i, k) * other(k, j);
        }
    }

    return product;
}

Math::Float2 Math::Matrix2::operator*(const Float2& vector) const {
    return Float2(
        (*this)(0, 0) * vector.x + (*this)(0, 1) * vector.y,
        (*this)(1, 0) * vector.x + (*this)(1, 1) * vector.y
    );
}

Math::Matrix2 Math::Matrix2::Inverse() const {
    Matrix2 inverse;

    inverse(0, 0) =   (*this)(1, 1);
    inverse(0, 1) = - (*this)(0, 1);
    inverse(1, 0) = - (*this)(1, 0);
    inverse(1, 1) =   (*this)(1, 0);

    return inverse * (1.0f / Determinant());
}

Math::Matrix2 Math::Matrix2::Transpose() const {
    Matrix2 transpose(*this);

    transpose(0, 1) = (*this)(1, 0);
    transpose(1, 0) = (*this)(0, 1);

    return transpose;
}

float Math::Matrix2::Determinant() const {
    return (*this)(0, 0) * (*this)(1, 1) - (*this)(0, 1) * (*this)(1, 0);
}


Math::Matrix3::Matrix3(float diagonal) {
    elements.fill(0.0f);

    (*this)(0, 0) = diagonal;
    (*this)(1, 1) = diagonal;
    (*this)(2, 2) = diagonal;
}

Math::Matrix3 Math::Matrix3::Fill(float scalar) {
    Matrix3 matrix;
    matrix.elements.fill(scalar);

    return matrix;
}

Math::Matrix3 Math::Matrix3::operator*(const Matrix3& other) const {
    Matrix3 product;

    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++) {
            for (size_t k = 0; k < 3; k++) product(i, j) += (*this)(i, k) * other(k, j);
        }
    }

    return product;
}

Math::Float3 Math::Matrix3::operator*(const Float3& vector) const {
    return Float3(
        (*this)(0, 0) * vector.x + (*this)(0, 1) * vector.y + (*this)(0, 2) * vector.z,
        (*this)(1, 0) * vector.x + (*this)(1, 1) * vector.y + (*this)(1, 2) * vector.z,
        (*this)(2, 0) * vector.x + (*this)(2, 1) * vector.y + (*this)(2, 2) * vector.z
    );
}

Math::Matrix3 Math::Matrix3::Inverse() const {
    Matrix3 inverse;

    inverse(0, 0) = (*this)(1, 1) * (*this)(2, 2) - (*this)(2, 1) * (*this)(1, 2);
    inverse(0, 1) = (*this)(0, 2) * (*this)(2, 1) - (*this)(0, 1) * (*this)(2, 2);
    inverse(0, 2) = (*this)(0, 1) * (*this)(1, 2) - (*this)(0, 2) * (*this)(1, 1);
    inverse(1, 0) = (*this)(1, 2) * (*this)(2, 0) - (*this)(1, 0) * (*this)(2, 2);
    inverse(1, 1) = (*this)(0, 0) * (*this)(2, 2) - (*this)(0, 2) * (*this)(2, 0);
    inverse(1, 2) = (*this)(1, 0) * (*this)(0, 2) - (*this)(0, 0) * (*this)(1, 2);
    inverse(2, 0) = (*this)(1, 0) * (*this)(2, 1) - (*this)(2, 0) * (*this)(1, 1);
    inverse(2, 1) = (*this)(2, 0) * (*this)(0, 1) - (*this)(0, 0) * (*this)(2, 1);
    inverse(2, 2) = (*this)(0, 0) * (*this)(1, 1) - (*this)(1, 0) * (*this)(0, 1);

    return inverse * (1.0f / Determinant());
}

Math::Matrix3 Math::Matrix3::Transpose() const {
    Matrix3 transpose(*this);

    transpose(0, 1) = (*this)(1, 0);
    transpose(0, 2) = (*this)(2, 0);

    transpose(1, 0) = (*this)(0, 1);
    transpose(1, 2) = (*this)(2, 1);

    transpose(2, 0) = (*this)(0, 2);
    transpose(2, 1) = (*this)(1, 2);

    return transpose;
}

float Math::Matrix3::Determinant() const {
    return (
        (*this)(0, 0) * ((*this)(1, 1) * (*this)(2, 2) - (*this)(2, 1) * (*this)(1, 2)) -
        (*this)(0, 1) * ((*this)(1, 0) * (*this)(2, 2) - (*this)(1, 2) * (*this)(2, 0)) +
        (*this)(0, 2) * ((*this)(1, 0) * (*this)(2, 1) - (*this)(1, 1) * (*this)(2, 0))
    );
}


Math::Matrix4::Matrix4(float diagonal) {
    elements.fill(0.0f);

    (*this)(0, 0) = diagonal;
    (*this)(1, 1) = diagonal;
    (*this)(2, 2) = diagonal;
    (*this)(3, 3) = diagonal;
}

Math::Matrix4 Math::Matrix4::Fill(float scalar) {
    Matrix4 matrix;
    matrix.elements.fill(scalar);

    return matrix;
}

Math::Matrix4 Math::Matrix4::Scale(const Float3& scale) {
    Matrix4 matrix(1.0f);

    matrix(0, 0) = scale.x;
    matrix(1, 1) = scale.y;
    matrix(2, 2) = scale.z;

    return matrix;
}

Math::Matrix4 Math::Matrix4::Translate(const Float3& translation) {
    Matrix4 matrix(1.0f);

    matrix(0, 3) = translation.x;
    matrix(1, 3) = translation.y;
    matrix(2, 3) = translation.z;

    return matrix;
}

Math::Matrix4 Math::Matrix4::Rotate(const Quaternion& quaternion) {
    Matrix4 rotation(1.0f);
    Quaternion normalized = quaternion.Normalize();

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

Math::Matrix4 Math::Matrix4::Rotate(const Float3& axis, float angle) {
    Matrix4 rotation(1.0f);

    float sine = sin(angle);
    float cosine = cos(angle);

    Float3 normalized = axis.Normalize();
    Float3 auxiliar = normalized * (1.0f - cosine);

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

Math::Matrix4 Math::Matrix4::Perspective(float fov, float aspect, float near, float far) {
    Matrix4 perspective;
    float tangent = tan(fov * 0.5f);

    perspective(0, 0) = 1.0f / (aspect * tangent);
    perspective(1, 1) = 1.0f / tangent;
    perspective(2, 2) = - (far + near) / (far - near);
    perspective(3, 2) = - 1.0f;
    perspective(2, 3) = - (2.0f * far * near) / (far - near);

    return perspective;
}

Math::Matrix4 Math::Matrix4::Orthographic(float left, float right, float bottom, float top, float near, float far) {
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

Math::Matrix4 Math::Matrix4::LookAt(const Float3& position, const Float3& target, const Float3& up) {
    Matrix4 look(1.0f);

    Float3 zaxis = (target - position).Normalize();
    Float3 xaxis = zaxis.Cross(up).Normalize();
    Float3 yaxis = zaxis.Cross(xaxis);

    look(0, 0) = xaxis.x;
    look(0, 1) = xaxis.y;
    look(0, 2) = xaxis.z;
    look(0, 3) = - xaxis.Dot(position);

    look(1, 0) = yaxis.x;
    look(1, 1) = yaxis.y;
    look(1, 2) = yaxis.z;
    look(1, 3) = - yaxis.Dot(position);

    look(2, 0) = - zaxis.x;
    look(2, 1) = - zaxis.y;
    look(2, 2) = - zaxis.z;
    look(2, 3) = zaxis.Dot(position);

    return look;
}

Math::Matrix4 Math::Matrix4::operator*(const Matrix4& other) const {
    Matrix4 product;

    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 4; j++) {
            for (size_t k = 0; k < 4; k++) product(i, j) += (*this)(i, k) * other(k, j);
        }
    }

    return product;
}

Math::Float4 Math::Matrix4::operator*(const Float4& vector) const {
    return Float4(
        (*this)(0, 0) * vector.x + (*this)(0, 1) * vector.y + (*this)(0, 2) * vector.z + (*this)(0, 3) * vector.w,
        (*this)(1, 0) * vector.x + (*this)(1, 1) * vector.y + (*this)(1, 2) * vector.z + (*this)(1, 3) * vector.w,
        (*this)(2, 0) * vector.x + (*this)(2, 1) * vector.y + (*this)(2, 2) * vector.z + (*this)(2, 3) * vector.w,
        (*this)(3, 0) * vector.x + (*this)(3, 1) * vector.y + (*this)(3, 2) * vector.z + (*this)(3, 3) * vector.w
    );
}

Math::Matrix4 Math::Matrix4::Inverse() const {
    Matrix4 inverse;

    inverse(0, 0) = (
        (*this)(1, 1) * (*this)(2, 2) * (*this)(3, 3) -
        (*this)(1, 1) * (*this)(3, 2) * (*this)(2, 3) -
        (*this)(1, 2) * (*this)(2, 1) * (*this)(3, 3) +
        (*this)(1, 2) * (*this)(3, 1) * (*this)(2, 3) +
        (*this)(1, 3) * (*this)(2, 1) * (*this)(3, 2) -
        (*this)(1, 3) * (*this)(3, 1) * (*this)(2, 2)
    );

    inverse(0, 1) = (
        - (*this)(0, 1) * (*this)(2, 2) * (*this)(3, 3) +
          (*this)(0, 1) * (*this)(3, 2) * (*this)(2, 3) +
          (*this)(0, 2) * (*this)(2, 1) * (*this)(3, 3) -
          (*this)(0, 2) * (*this)(3, 1) * (*this)(2, 3) -
          (*this)(0, 3) * (*this)(2, 1) * (*this)(3, 2) +
          (*this)(0, 3) * (*this)(3, 1) * (*this)(2, 2)
    );

    inverse(0, 2) = (
        (*this)(0, 1) * (*this)(1, 2) * (*this)(3, 3) -
        (*this)(0, 1) * (*this)(3, 2) * (*this)(1, 3) -
        (*this)(0, 2) * (*this)(1, 1) * (*this)(3, 3) +
        (*this)(0, 2) * (*this)(3, 1) * (*this)(1, 3) +
        (*this)(0, 3) * (*this)(1, 1) * (*this)(3, 2) -
        (*this)(0, 3) * (*this)(3, 1) * (*this)(1, 2)
    );

    inverse(0, 3) = (
        - (*this)(0, 1) * (*this)(1, 2) * (*this)(2, 3) +
          (*this)(0, 1) * (*this)(2, 2) * (*this)(1, 3) +
          (*this)(0, 2) * (*this)(1, 1) * (*this)(2, 3) -
          (*this)(0, 2) * (*this)(2, 1) * (*this)(1, 3) -
          (*this)(0, 3) * (*this)(1, 1) * (*this)(2, 2) +
          (*this)(0, 3) * (*this)(2, 1) * (*this)(1, 2)
    );

    inverse(1, 0) = (
        - (*this)(1, 0) * (*this)(2, 2) * (*this)(3, 3) +
          (*this)(1, 0) * (*this)(3, 2) * (*this)(2, 3) +
          (*this)(1, 2) * (*this)(2, 0) * (*this)(3, 3) -
          (*this)(1, 2) * (*this)(3, 0) * (*this)(2, 3) -
          (*this)(1, 3) * (*this)(2, 0) * (*this)(3, 2) +
          (*this)(1, 3) * (*this)(3, 0) * (*this)(2, 2)
    );

    inverse(1, 1) = (
        (*this)(0, 0) * (*this)(2, 2) * (*this)(3, 3) -
        (*this)(0, 0) * (*this)(3, 2) * (*this)(2, 3) -
        (*this)(0, 2) * (*this)(2, 0) * (*this)(3, 3) +
        (*this)(0, 2) * (*this)(3, 0) * (*this)(2, 3) +
        (*this)(0, 3) * (*this)(2, 0) * (*this)(3, 2) -
        (*this)(0, 3) * (*this)(3, 0) * (*this)(2, 2)
    );

    inverse(1, 2) = (
        - (*this)(0, 0) * (*this)(1, 2) * (*this)(3, 3) +
          (*this)(0, 0) * (*this)(3, 2) * (*this)(1, 3) +
          (*this)(0, 2) * (*this)(1, 0) * (*this)(3, 3) -
          (*this)(0, 2) * (*this)(3, 0) * (*this)(1, 3) -
          (*this)(0, 3) * (*this)(1, 0) * (*this)(3, 2) +
          (*this)(0, 3) * (*this)(3, 0) * (*this)(1, 2)
    );

    inverse(1, 3) = (
        (*this)(0, 0) * (*this)(1, 2) * (*this)(2, 3) -
        (*this)(0, 0) * (*this)(2, 2) * (*this)(1, 3) -
        (*this)(0, 2) * (*this)(1, 0) * (*this)(2, 3) +
        (*this)(0, 2) * (*this)(2, 0) * (*this)(1, 3) +
        (*this)(0, 3) * (*this)(1, 0) * (*this)(2, 2) -
        (*this)(0, 3) * (*this)(2, 0) * (*this)(1, 2)
    );

    inverse(2, 0) = (
        (*this)(1, 0) * (*this)(2, 1) * (*this)(3, 3) -
        (*this)(1, 0) * (*this)(3, 1) * (*this)(2, 3) -
        (*this)(1, 1) * (*this)(2, 0) * (*this)(3, 3) +
        (*this)(1, 1) * (*this)(3, 0) * (*this)(2, 3) +
        (*this)(1, 3) * (*this)(2, 0) * (*this)(3, 1) -
        (*this)(1, 3) * (*this)(3, 0) * (*this)(2, 1)
    );

    inverse(2, 1) = (
        - (*this)(0, 0) * (*this)(2, 1) * (*this)(3, 3) +
          (*this)(0, 0) * (*this)(3, 1) * (*this)(2, 3) +
          (*this)(0, 1) * (*this)(2, 0) * (*this)(3, 3) -
          (*this)(0, 1) * (*this)(3, 0) * (*this)(2, 3) -
          (*this)(0, 3) * (*this)(2, 0) * (*this)(3, 1) +
          (*this)(0, 3) * (*this)(3, 0) * (*this)(2, 1)
    );

    inverse(2, 2) = (
        (*this)(0, 0) * (*this)(1, 1) * (*this)(3, 3) -
        (*this)(0, 0) * (*this)(3, 1) * (*this)(1, 3) -
        (*this)(0, 1) * (*this)(1, 0) * (*this)(3, 3) +
        (*this)(0, 1) * (*this)(3, 0) * (*this)(1, 3) +
        (*this)(0, 3) * (*this)(1, 0) * (*this)(3, 1) -
        (*this)(0, 3) * (*this)(3, 0) * (*this)(1, 1)
    );

    inverse(2, 3) = (
        - (*this)(0, 0) * (*this)(1, 1) * (*this)(2, 3) +
          (*this)(0, 0) * (*this)(2, 1) * (*this)(1, 3) +
          (*this)(0, 1) * (*this)(1, 0) * (*this)(2, 3) -
          (*this)(0, 1) * (*this)(2, 0) * (*this)(1, 3) -
          (*this)(0, 3) * (*this)(1, 0) * (*this)(2, 1) +
          (*this)(0, 3) * (*this)(2, 0) * (*this)(1, 1)
    );

    inverse(3, 0) = (
        - (*this)(1, 0) * (*this)(2, 1) * (*this)(3, 2) +
          (*this)(1, 0) * (*this)(3, 1) * (*this)(2, 2) +
          (*this)(1, 1) * (*this)(2, 0) * (*this)(3, 2) -
          (*this)(1, 1) * (*this)(3, 0) * (*this)(2, 2) -
          (*this)(1, 2) * (*this)(2, 0) * (*this)(3, 1) +
          (*this)(1, 2) * (*this)(3, 0) * (*this)(2, 1)
    );

    inverse(3, 1) = (
        (*this)(0, 0) * (*this)(2, 1) * (*this)(3, 2) -
        (*this)(0, 0) * (*this)(3, 1) * (*this)(2, 2) -
        (*this)(0, 1) * (*this)(2, 0) * (*this)(3, 2) +
        (*this)(0, 1) * (*this)(3, 0) * (*this)(2, 2) +
        (*this)(0, 2) * (*this)(2, 0) * (*this)(3, 1) -
        (*this)(0, 2) * (*this)(3, 0) * (*this)(2, 1)
    );

    inverse(3, 2) = (
        - (*this)(0, 0) * (*this)(1, 1) * (*this)(3, 2) +
          (*this)(0, 0) * (*this)(3, 1) * (*this)(1, 2) +
          (*this)(0, 1) * (*this)(1, 0) * (*this)(3, 2) -
          (*this)(0, 1) * (*this)(3, 0) * (*this)(1, 2) -
          (*this)(0, 2) * (*this)(1, 0) * (*this)(3, 1) +
          (*this)(0, 2) * (*this)(3, 0) * (*this)(1, 1)
    );

    inverse(3, 3) = (
        (*this)(0, 0) * (*this)(1, 1) * (*this)(2, 2) -
        (*this)(0, 0) * (*this)(2, 1) * (*this)(1, 2) -
        (*this)(0, 1) * (*this)(1, 0) * (*this)(2, 2) +
        (*this)(0, 1) * (*this)(2, 0) * (*this)(1, 2) +
        (*this)(0, 2) * (*this)(1, 0) * (*this)(2, 1) -
        (*this)(0, 2) * (*this)(2, 0) * (*this)(1, 1)
    );

    float determinant = (*this)(0, 0) * inverse(0, 0) + (*this)(1, 0) * inverse(0, 1) + (*this)(2, 0) * inverse(0, 2) + (*this)(3, 0) * inverse(0, 3);
    return inverse * (1.0f / determinant);
}

Math::Matrix4 Math::Matrix4::Transpose() const {
    Matrix4 transpose(*this);

    transpose(0, 1) = (*this)(1, 0);
    transpose(0, 2) = (*this)(2, 0);
    transpose(0, 3) = (*this)(3, 0);

    transpose(1, 0) = (*this)(0, 1);
    transpose(1, 2) = (*this)(2, 1);
    transpose(1, 3) = (*this)(3, 1);

    transpose(2, 0) = (*this)(0, 2);
    transpose(2, 1) = (*this)(1, 2);
    transpose(2, 3) = (*this)(3, 2);

    transpose(3, 0) = (*this)(0, 3);
    transpose(3, 1) = (*this)(1, 3);
    transpose(3, 2) = (*this)(2, 3);

    return transpose;
}

float Math::Matrix4::Determinant() const {
    return (
        (*this)(0, 3) * (*this)(1, 2) * (*this)(2, 1) * (*this)(3, 0) - (*this)(0, 2) * (*this)(1, 3) * (*this)(2, 1) * (*this)(3, 0) -
        (*this)(0, 3) * (*this)(1, 1) * (*this)(2, 2) * (*this)(3, 0) + (*this)(0, 1) * (*this)(1, 3) * (*this)(2, 2) * (*this)(3, 0) +
        (*this)(0, 2) * (*this)(1, 1) * (*this)(2, 3) * (*this)(3, 0) - (*this)(0, 1) * (*this)(1, 2) * (*this)(2, 3) * (*this)(3, 0) -
        (*this)(0, 3) * (*this)(1, 2) * (*this)(2, 0) * (*this)(3, 1) + (*this)(0, 2) * (*this)(1, 3) * (*this)(2, 0) * (*this)(3, 1) +
        (*this)(0, 3) * (*this)(1, 0) * (*this)(2, 2) * (*this)(3, 1) - (*this)(0, 0) * (*this)(1, 3) * (*this)(2, 2) * (*this)(3, 1) -
        (*this)(0, 2) * (*this)(1, 0) * (*this)(2, 3) * (*this)(3, 1) + (*this)(0, 0) * (*this)(1, 2) * (*this)(2, 3) * (*this)(3, 1) +
        (*this)(0, 3) * (*this)(1, 1) * (*this)(2, 0) * (*this)(3, 2) - (*this)(0, 1) * (*this)(1, 3) * (*this)(2, 0) * (*this)(3, 2) -
        (*this)(0, 3) * (*this)(1, 0) * (*this)(2, 1) * (*this)(3, 2) + (*this)(0, 0) * (*this)(1, 3) * (*this)(2, 1) * (*this)(3, 2) +
        (*this)(0, 1) * (*this)(1, 0) * (*this)(2, 3) * (*this)(3, 2) - (*this)(0, 0) * (*this)(1, 1) * (*this)(2, 3) * (*this)(3, 2) -
        (*this)(0, 2) * (*this)(1, 1) * (*this)(2, 0) * (*this)(3, 3) + (*this)(0, 1) * (*this)(1, 2) * (*this)(2, 0) * (*this)(3, 3) +
        (*this)(0, 2) * (*this)(1, 0) * (*this)(2, 1) * (*this)(3, 3) - (*this)(0, 0) * (*this)(1, 2) * (*this)(2, 1) * (*this)(3, 3) -
        (*this)(0, 1) * (*this)(1, 0) * (*this)(2, 2) * (*this)(3, 3) + (*this)(0, 0) * (*this)(1, 1) * (*this)(2, 2) * (*this)(3, 3)
    );
}
