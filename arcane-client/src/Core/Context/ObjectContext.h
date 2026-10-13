#pragma once

#include <DirectXMath.h>
#include <span>

namespace Core
{
    struct ObjectContext
    {
        DirectX::XMMATRIX WorldMatrix;
        DirectX::XMMATRIX WorldViewProjectionMatrix;
        std::span<const DirectX::XMMATRIX> WorldMatrixInstances;
    };
}
