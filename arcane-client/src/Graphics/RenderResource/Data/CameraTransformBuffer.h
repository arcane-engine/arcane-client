#pragma once

#include <DirectXMath.h>

namespace Graphics
{
    class RenderContext;

    struct CameraTransformBuffer
    {
        DirectX::XMMATRIX ViewMatrix;
        DirectX::XMMATRIX ProjectionMatrix;

        CameraTransformBuffer() = default;
        CameraTransformBuffer(const DirectX::XMMATRIX& viewMatrix, const DirectX::XMMATRIX& projectionMatrix) noexcept;

        static CameraTransformBuffer FromRenderContext(const RenderContext& renderContext) noexcept;
    };
}
