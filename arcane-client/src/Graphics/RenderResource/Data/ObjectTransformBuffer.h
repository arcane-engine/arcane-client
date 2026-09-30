#pragma once

#include <DirectXMath.h>

namespace Graphics
{
    class RenderContext;

    struct ObjectTransformBuffer
    {
        DirectX::XMMATRIX WorldMatrix;
        DirectX::XMMATRIX WorldViewProjectionMatrix;
        
        ObjectTransformBuffer(const DirectX::XMMATRIX& worldMatrix, const DirectX::XMMATRIX& worldViewProjectionMatrix) noexcept;

        static ObjectTransformBuffer FromRenderContext(const RenderContext& renderContext) noexcept;
    };
}
