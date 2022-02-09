#pragma once


#include "Precompiled.hpp"
#include "Math/Vector.hpp"
#include "Math/Quaternion.hpp"


#define __MatrixFunctions__(type)                                                                                                                           \
    static type Identity() { return type(1.0f); }                                                                                                           \
                                                                                                                                                            \
    friend type operator*(const type& first, const type& second);                                                                                           \
    type& operator*=(const type& other) { *this = *this * other; return *this; }                                                                            \
                                                                                                                                                            \
    type& operator+=(const type& other) { for (std::size_t i = 0; i < elements.size(); i++) elements[i] += other.elements[i]; return *this; }               \
    type& operator-=(const type& other) { for (std::size_t i = 0; i < elements.size(); i++) elements[i] -= other.elements[i]; return *this; }               \
                                                                                                                                                            \
    friend type operator+(type first, const type& second) { return first += second; }                                                                       \
    friend type operator-(type first, const type& second) { return first -= second; }                                                                       \
                                                                                                                                                            \
    type& operator+=(float scalar) { for (float& element : elements) element += scalar; return *this; }                                                     \
    type& operator-=(float scalar) { for (float& element : elements) element -= scalar; return *this; }                                                     \
    type& operator*=(float scalar) { for (float& element : elements) element *= scalar; return *this; }                                                     \
    type& operator/=(float scalar) { for (float& element : elements) element /= scalar; return *this; }                                                     \
                                                                                                                                                            \
    friend type operator+(type matrix, float scalar) { return matrix += scalar; }                                                                           \
    friend type operator-(type matrix, float scalar) { return matrix -= scalar; }                                                                           \
    friend type operator*(type matrix, float scalar) { return matrix *= scalar; }                                                                           \
    friend type operator/(type matrix, float scalar) { return matrix /= scalar; }                                                                           \
                                                                                                                                                            \
    friend type operator-(const type& matrix) { return matrix * -1.0f; }                                                                                    \
                                                                                                                                                            \
    operator std::string() const {                                                                                                                          \
        std::stringstream stream;                                                                                                                           \
        stream << std::fixed << std::setprecision(2);                                                                                                       \
        stream << '['; for (std::size_t i = 0; i < elements.size() - 1; i++) stream << elements[i] << ", "; stream << elements[elements.size() - 1] << ']'; \
        return stream.str();                                                                                                                                \
    }                                                                                                                                                       \


// TODO: Use operator<<()
namespace Feather::Math {
    class Matrix2 {
    public:
        Matrix2(float diagonal = 0.0f);
        Matrix2(std::array<float, 2 * 2> elements): elements(elements) {}

        float& operator()(std::size_t row, std::size_t column) { return elements[row + column * 2]; }
        float operator()(std::size_t row, std::size_t column) const { return elements[row + column * 2]; }

        __MatrixFunctions__(Matrix2);
    private:
        std::array<float, 2 * 2> elements;
    };

    Matrix2 operator*(const Matrix2& first, const Matrix2& second);
    Vector2 operator*(const Matrix2& matrix, const Vector2& vector);

    Matrix2 Inverse(const Matrix2& matrix);
    Matrix2 Transpose(const Matrix2& matrix);
    float Determinant(const Matrix2& matrix);


    class Matrix3 {
    public:
        Matrix3(float diagonal = 0.0f);
        Matrix3(std::array<float, 3 * 3> elements): elements(elements) {}

        float& operator()(std::size_t row, std::size_t column) { return elements[row + column * 3]; }
        float operator()(std::size_t row, std::size_t column) const { return elements[row + column * 3]; }

        __MatrixFunctions__(Matrix3);
    private:
        std::array<float, 3 * 3> elements;
    };

    Matrix3 operator*(const Matrix3& first, const Matrix3& second);
    Vector3 operator*(const Matrix3& matrix, const Vector3& vector);

    Matrix3 Inverse(const Matrix3& matrix);
    Matrix3 Transpose(const Matrix3& matrix);
    float Determinant(const Matrix3& matrix);


    class Matrix4 {
    public:
        Matrix4(float diagonal = 0.0f);
        Matrix4(std::array<float, 4 * 4> elements): elements(elements) {}

        float& operator()(std::size_t row, std::size_t column) { return elements[row + column * 4]; }
        float operator()(std::size_t row, std::size_t column) const { return elements[row + column * 4]; }

        __MatrixFunctions__(Matrix4);
    private:
        std::array<float, 4 * 4> elements;
    };

    Matrix4 operator*(const Matrix4& first, const Matrix4& second);
    Vector4 operator*(const Matrix4& matrix, const Vector4& vector);

    Matrix4 Inverse(const Matrix4& matrix);
    Matrix4 Transpose(const Matrix4& matrix);
    float Determinant(const Matrix4& matrix);

    Matrix4 Scale(const Vector3& scale);
    Matrix4 Translate(const Vector3& translation);
    Matrix4 Rotate(const Vector3& axis, float angle);
    Matrix4 Rotate(const Quaternion& quaternion);

    // TODO: Add Inifinite Perspective
    Matrix4 Perspective(float fov, float aspect, float near, float far);
    Matrix4 Orthographic(float left, float right, float bottom, float top, float near, float far);
    Matrix4 Look(const Vector3& position, const Vector3& target, const Vector3& up = { 0.0f, 1.0f, 0.0f });
}
