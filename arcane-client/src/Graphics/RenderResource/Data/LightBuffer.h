#pragma once

#include <DirectXMath.h>
#include <span>

namespace Core
{
    struct Context;
}

namespace Graphics
{
    struct LightBuffer
    {
        DirectX::XMFLOAT4 Positions[4];
        DirectX::XMFLOAT4 Colors[4];

        LightBuffer();
        LightBuffer(std::span<const DirectX::XMFLOAT4> positions, std::span<const DirectX::XMFLOAT4> colors) noexcept;

        static LightBuffer FromContext(const Core::Context& context) noexcept;
    };
}
