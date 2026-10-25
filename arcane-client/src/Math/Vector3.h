// ReSharper disable CppNonExplicitConvertingConstructor

#pragma once

#include <array>
#include <DirectXMath.h>

namespace Math
{
    struct Vector3
    {
        float X;
        float Y;
        float Z;

        Vector3() = default;
        Vector3(float x, float y, float z) noexcept;
        Vector3(const std::array<float, 3>& array) noexcept;

        Vector3& operator=(const DirectX::XMVECTOR& vector) noexcept;
        Vector3& operator=(const std::array<float, 3>& array) noexcept;

        bool operator==(const Vector3&) const = default;

        Vector3 operator*(float value) const noexcept;

        Vector3 operator+(const Vector3& value) const noexcept;
        Vector3 operator-(const Vector3& value) const noexcept;

        explicit operator DirectX::XMVECTOR() const;

        [[nodiscard]] float GetLength() const noexcept;
        [[nodiscard]] Vector3 GetNormalized() const noexcept;

        [[nodiscard]] DirectX::XMMATRIX GetTranslationMatrix() const noexcept;
        [[nodiscard]] DirectX::XMMATRIX GetScalingMatrix() const noexcept;

        void Normalize() noexcept;
    };
}
