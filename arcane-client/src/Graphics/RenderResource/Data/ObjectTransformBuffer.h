#pragma once

#include <DirectXMath.h>

namespace Core
{
    struct Context;
}

namespace Graphics
{
    struct ObjectTransformBuffer
    {
        DirectX::XMMATRIX WorldMatrix;
        DirectX::XMMATRIX WorldViewProjectionMatrix;
        
        ObjectTransformBuffer() = default;
        ObjectTransformBuffer(const DirectX::XMMATRIX& worldMatrix, const DirectX::XMMATRIX& worldViewProjectionMatrix) noexcept;

        static ObjectTransformBuffer FromContext(const Core::Context& context) noexcept;
    };
}
