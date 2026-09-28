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

        operator DirectX::XMVECTOR() const;
    };
}
