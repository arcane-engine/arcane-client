#include "LightBuffer.h"

#include <cstring>

#include "Graphics/RenderContext.h"

namespace Graphics
{
    LightBuffer::LightBuffer()
    {
        std::memset(this, 0, sizeof(*this));
    }

    LightBuffer::LightBuffer(const std::span<const DirectX::XMFLOAT4> positions, const std::span<const DirectX::XMFLOAT4> colors) noexcept : LightBuffer()
    {
        const auto count = std::min(positions.size(), std::size(Positions));

        std::copy_n(positions.begin(), count, Positions);
        std::copy_n(colors.begin(), count, Colors);
    }

    LightBuffer LightBuffer::FromRenderContext(const RenderContext& renderContext) noexcept
    {
        LightBuffer result;
        
        for (auto i = 0; i < 4 ; i++)
        {
            result.Positions[i] = renderContext.Lights[i].Position;
            result.Colors[i] = renderContext.Lights[i].Color;
        }

        return result;
    }
}
