#pragma once

#include <DirectXMath.h>

namespace Graphics
{
    class RenderContext
    {
    public:
        RenderContext(const DirectX::XMMATRIX& viewMatrix, const DirectX::XMMATRIX& projectionMatrix) noexcept;

        DirectX::XMMATRIX WorldMatrix;
        DirectX::XMMATRIX ViewMatrix;
        DirectX::XMMATRIX ProjectionMatrix;
        DirectX::XMMATRIX ViewProjectionMatrix;
        DirectX::XMMATRIX WorldViewProjectionMatrix;
    };
}
