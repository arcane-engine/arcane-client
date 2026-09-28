#pragma once

#include <DirectXMath.h>

namespace Graphics
{
    struct ObjectTransformBuffer
    {
        DirectX::XMMATRIX WorldMatrix;
        DirectX::XMMATRIX WorldViewProjectionMatrix;
        
        ObjectTransformBuffer() noexcept = default;
        explicit ObjectTransformBuffer(const DirectX::XMMATRIX& worldMatrix, const DirectX::XMMATRIX& worldViewProjectionMatrix) noexcept;
    };
}
