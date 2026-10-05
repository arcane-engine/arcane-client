#pragma once

#include <DirectXMath.h>
#include <span>
#include <vector>

namespace Graphics
{
    struct Light
    {
        DirectX::XMFLOAT4 Position;
        DirectX::XMFLOAT4 Color;
    };

    class RenderContext
    {
    public:
        RenderContext(const DirectX::XMMATRIX& viewMatrix, const DirectX::XMMATRIX& projectionMatrix) noexcept;

        DirectX::XMMATRIX WorldMatrix;
        DirectX::XMMATRIX ViewMatrix;
        DirectX::XMMATRIX ProjectionMatrix;
        DirectX::XMMATRIX ViewProjectionMatrix;
        DirectX::XMMATRIX WorldViewProjectionMatrix;
        std::vector<Light> Lights;
        std::span<const DirectX::XMMATRIX> InstanceMatrices;
    };
}
