#pragma once

#include <DirectXMath.h>

#include "Math/Vector3.h"

namespace Core
{
    struct CameraContext
    {
        bool Changed = false;
        Math::Vector3 Target;
        Math::Vector3 Direction;
        DirectX::XMMATRIX ViewMatrix;
        DirectX::XMMATRIX ProjectionMatrix;
        DirectX::XMMATRIX ViewProjectionMatrix;
    };
}
