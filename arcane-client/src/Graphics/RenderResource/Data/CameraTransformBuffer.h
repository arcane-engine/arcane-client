#pragma once

#include <DirectXMath.h>

namespace Graphics
{
    struct CameraTransformBuffer
    {
        DirectX::XMMATRIX ViewMatrix;
        DirectX::XMMATRIX ProjectionMatrix;

        CameraTransformBuffer() noexcept = default;
        CameraTransformBuffer(const DirectX::XMMATRIX& viewMatrix, const DirectX::XMMATRIX& projectionMatrix) noexcept;
    };
}
