#pragma once


#include "Precompiled.hpp"
#include "Math/Vector.hpp"
#include "Math/Quaternion.hpp"

namespace Feather::Math {
    class Matrix2 {
    public:
        Matrix2(float diagonal = 0.0f);
        Matrix2(std::array<float, 2 * 2> elements): elements(elements) {}

        static Matrix2 Identity() { return Matrix2(1.0f); }


        Matrix2 operator*(const Matrix2& other) const;
        Float2 operator*(const Float2& vector) const;

        Matrix2& operator+=(const Matrix2& other) { for (std::size_t i = 0; i < 2 * 2; i++) elements[i] += other.elements[i]; return *this; }
        Matrix2& operator-=(const Matrix2& other) { for (std::size_t i = 0; i < 2 * 2; i++) elements[i] -= other.elements[i]; return *this; }
        Matrix2& operator*=(const Matrix2& other) { *this = *this * other; return *this; }

        Matrix2 operator+(const Matrix2& second) const { return Matrix2(*this) += second; }
        Matrix2 operator-(const Matrix2& second) const { return Matrix2(*this) -= second; }

        Matrix2& operator+=(float scalar) { for (float& element : elements) element += scalar; return *this; }
        Matrix2& operator-=(float scalar) { for (float& element : elements) element -= scalar; return *this; }
        Matrix2& operator*=(float scalar) { for (float& element : elements) element *= scalar; return *this; }
        Matrix2& operator/=(float scalar) { for (float& element : elements) element /= scalar; return *this; }

        Matrix2 operator+(float scalar) const { return Matrix2(*this) += scalar; }
        Matrix2 operator-(float scalar) const { return Matrix2(*this) -= scalar; }
        Matrix2 operator*(float scalar) const { return Matrix2(*this) *= scalar; }
        Matrix2 operator/(float scalar) const { return Matrix2(*this) /= scalar; }

        Matrix2 operator+() const { return *this; }
        Matrix2 operator-() const { return *this * 1.0f; }


        float& operator()(std::size_t row, std::size_t column) { return elements[row + column * 2]; }
        float operator()(std::size_t row, std::size_t column) const { return elements[row + column * 2]; }


        friend std::ostream& operator<<(std::ostream& stream, const Matrix2& matrix) {
            std::ios::fmtflags flags(stream.flags());

            stream << std::fixed << std::setprecision(2);
            stream << '['; for (std::size_t i = 0; i < 2 * 2 - 1; i++) stream << matrix.elements[i] << ", "; stream << matrix.elements[2 * 2 - 1] << ']';

            stream.flags(flags);
            return stream;
        }


        operator const float*() const { return elements.data(); }


        Matrix2 Inverse() const;
        Matrix2 Transpose() const;
        float Determinant() const;
    private:
        std::array<float, 2 * 2> elements;
    };


    class Matrix3 {
    public:
        Matrix3(float diagonal = 0.0f);
        Matrix3(std::array<float, 3 * 3> elements): elements(elements) {}

        static Matrix3 Identity() { return Matrix3(1.0f); }


        Matrix3 operator*(const Matrix3& other) const;
        Float3 operator*(const Float3& vector) const;

        Matrix3& operator+=(const Matrix3& other) { for (std::size_t i = 0; i < 3 * 3; i++) elements[i] += other.elements[i]; return *this; }
        Matrix3& operator-=(const Matrix3& other) { for (std::size_t i = 0; i < 3 * 3; i++) elements[i] -= other.elements[i]; return *this; }
        Matrix3& operator*=(const Matrix3& other) { *this = *this * other; return *this; }

        Matrix3 operator+(const Matrix3& second) const { return Matrix3(*this) += second; }
        Matrix3 operator-(const Matrix3& second) const { return Matrix3(*this) -= second; }

        Matrix3& operator+=(float scalar) { for (float& element : elements) element += scalar; return *this; }
        Matrix3& operator-=(float scalar) { for (float& element : elements) element -= scalar; return *this; }
        Matrix3& operator*=(float scalar) { for (float& element : elements) element *= scalar; return *this; }
        Matrix3& operator/=(float scalar) { for (float& element : elements) element /= scalar; return *this; }

        Matrix3 operator+(float scalar) const { return Matrix3(*this) += scalar; }
        Matrix3 operator-(float scalar) const { return Matrix3(*this) -= scalar; }
        Matrix3 operator*(float scalar) const { return Matrix3(*this) *= scalar; }
        Matrix3 operator/(float scalar) const { return Matrix3(*this) /= scalar; }

        Matrix3 operator+() const { return *this; }
        Matrix3 operator-() const { return *this * 1.0f; }


        float& operator()(std::size_t row, std::size_t column) { return elements[row + column * 3]; }
        float operator()(std::size_t row, std::size_t column) const { return elements[row + column * 3]; }


        friend std::ostream& operator<<(std::ostream& stream, const Matrix3& matrix) {
            std::ios::fmtflags flags(stream.flags());

            stream << std::fixed << std::setprecision(2);
            stream << '['; for (std::size_t i = 0; i < 3 * 3 - 1; i++) stream << matrix.elements[i] << ", "; stream << matrix.elements[3 * 3 - 1] << ']';

            stream.flags(flags);
            return stream;
        }


        operator const float*() const { return elements.data(); }


        Matrix3 Inverse() const;
        Matrix3 Transpose() const;
        float Determinant() const;
    private:
        std::array<float, 3 * 3> elements;
    };


    class Matrix4 {
    public:
        Matrix4(float diagonal = 0.0f);
        Matrix4(std::array<float, 4 * 4> elements): elements(elements) {}

        static Matrix4 Identity() { return Matrix4(1.0f); }


        static Matrix4 Scale(const Float3& scale);
        static Matrix4 Translate(const Float3& translation);

        static Matrix4 Rotate(const Quaternion& quaternion);
        static Matrix4 Rotate(const Float3& axis, float angle);


        // TODO: Add Inifinite Perspective
        static Matrix4 Perspective(float fov, float aspect, float near, float far);
        static Matrix4 Orthographic(float left, float right, float bottom, float top, float near, float far);
        static Matrix4 LookAt(const Float3& position, const Float3& target, const Float3& up = { 0.0f, 1.0f, 0.0f });


        Matrix4 operator*(const Matrix4& other) const;
        Float4 operator*(const Float4& vector) const;

        Matrix4& operator+=(const Matrix4& other) { for (std::size_t i = 0; i < 4 * 4; i++) elements[i] += other.elements[i]; return *this; }
        Matrix4& operator-=(const Matrix4& other) { for (std::size_t i = 0; i < 4 * 4; i++) elements[i] -= other.elements[i]; return *this; }
        Matrix4& operator*=(const Matrix4& other) { *this = *this * other; return *this; }

        Matrix4 operator+(const Matrix4& second) const { return Matrix4(*this) += second; }
        Matrix4 operator-(const Matrix4& second) const { return Matrix4(*this) -= second; }

        Matrix4& operator+=(float scalar) { for (float& element : elements) element += scalar; return *this; }
        Matrix4& operator-=(float scalar) { for (float& element : elements) element -= scalar; return *this; }
        Matrix4& operator*=(float scalar) { for (float& element : elements) element *= scalar; return *this; }
        Matrix4& operator/=(float scalar) { for (float& element : elements) element /= scalar; return *this; }

        Matrix4 operator+(float scalar) const { return Matrix4(*this) += scalar; }
        Matrix4 operator-(float scalar) const { return Matrix4(*this) -= scalar; }
        Matrix4 operator*(float scalar) const { return Matrix4(*this) *= scalar; }
        Matrix4 operator/(float scalar) const { return Matrix4(*this) /= scalar; }

        Matrix4 operator+() const { return *this; }
        Matrix4 operator-() const { return *this * 1.0f; }


        float& operator()(std::size_t row, std::size_t column) { return elements[row + column * 4]; }
        float operator()(std::size_t row, std::size_t column) const { return elements[row + column * 4]; }


        friend std::ostream& operator<<(std::ostream& stream, const Matrix4& matrix) {
            std::ios::fmtflags flags(stream.flags());

            stream << std::fixed << std::setprecision(2);
            stream << '['; for (std::size_t i = 0; i < 4 * 4 - 1; i++) stream << matrix.elements[i] << ", "; stream << matrix.elements[4 * 4 - 1] << ']';

            stream.flags(flags);
            return stream;
        }


        operator const float*() const { return elements.data(); }


        Matrix4 Inverse() const;
        Matrix4 Transpose() const;
        float Determinant() const;
    private:
        std::array<float, 4 * 4> elements;
    };
}
