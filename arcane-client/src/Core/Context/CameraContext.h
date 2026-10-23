#pragma once

#include <DirectXMath.h>

#include "Math/Vector3.h"

namespace Core
{
    struct CameraContext
    {
        Math::Vector3 Target;
        Math::Vector3 Velocity;
        DirectX::XMMATRIX ViewMatrix;
        DirectX::XMMATRIX ProjectionMatrix;
        DirectX::XMMATRIX ViewProjectionMatrix;
    };
}
