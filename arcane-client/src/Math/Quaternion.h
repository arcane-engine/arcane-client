#pragma once

#include <DirectXMath.h>

namespace Math
{
    struct Quaternion
    {
        float X;
        float Y;
        float Z;
        float W;

        explicit operator DirectX::XMVECTOR() const;
    };
}
