#pragma once

#include <DirectXMath.h>

namespace Core
{
    struct Context;
}

namespace Graphics
{
    struct CameraTransformBuffer
    {
        DirectX::XMMATRIX ViewMatrix;
        DirectX::XMMATRIX ProjectionMatrix;

        CameraTransformBuffer() = default;
        CameraTransformBuffer(const DirectX::XMMATRIX& viewMatrix, const DirectX::XMMATRIX& projectionMatrix) noexcept;

        static CameraTransformBuffer FromContext(const Core::Context& context) noexcept;
    };
}
