#pragma once

#include <DirectXMath.h>

namespace Core
{
    struct CameraContext
    {
        DirectX::XMMATRIX ViewMatrix;
        DirectX::XMMATRIX ProjectionMatrix;
        DirectX::XMMATRIX ViewProjectionMatrix;
    };
}
