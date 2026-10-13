#pragma once

#include <DirectXMath.h>

namespace Core
{
    struct ObjectContext
    {
        DirectX::XMMATRIX WorldMatrix;
        DirectX::XMMATRIX WorldViewProjectionMatrix;
    };
}
