#pragma once

#include <DirectXMath.h>

namespace Math
{
    struct Vector3
    {
        float X;
        float Y;
        float Z;

        Vector3& operator=(const DirectX::XMVECTOR& vector) noexcept;

        Vector3 operator*(float value) const noexcept;

        Vector3 operator+(const Vector3& value) const noexcept;
        Vector3 operator-(const Vector3& value) const noexcept;

        explicit operator DirectX::XMVECTOR() const;

        [[nodiscard]] float GetLength() const noexcept;
        [[nodiscard]] Vector3 GetNormalized() const noexcept;

        void Normalize() noexcept;
    };
}
