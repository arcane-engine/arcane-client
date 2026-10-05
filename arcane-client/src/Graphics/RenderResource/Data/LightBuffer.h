#pragma once

#include <DirectXMath.h>
#include <span>

namespace Graphics
{
    class RenderContext;

    struct LightBuffer
    {
        DirectX::XMFLOAT4 Positions[4];
        DirectX::XMFLOAT4 Colors[4];

        LightBuffer();
        LightBuffer(std::span<const DirectX::XMFLOAT4> positions, std::span<const DirectX::XMFLOAT4> colors) noexcept;

        static LightBuffer FromRenderContext(const RenderContext& renderContext) noexcept;
    };
}
