// ReSharper disable CppNonExplicitConvertingConstructor

#pragma once

#include <array>
#include <DirectXMath.h>

namespace Math
{
    struct Quaternion
    {
        float X;
        float Y;
        float Z;
        float W;

        Quaternion() = default;
        Quaternion(float x, float y, float z, float w) noexcept;
        Quaternion(const std::array<float, 4>& array) noexcept;

        Quaternion& operator=(const DirectX::XMVECTOR& vector) noexcept;
        Quaternion& operator=(const std::array<float, 4>& array) noexcept;

        explicit operator DirectX::XMVECTOR() const;

        [[nodiscard]] DirectX::XMMATRIX GetRotationMatrix() const noexcept;
    };
}
