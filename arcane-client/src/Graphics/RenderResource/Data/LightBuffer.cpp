#include "LightBuffer.h"

#include <cstring>

#include "Core/Context/Context.h"

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

    LightBuffer LightBuffer::FromContext(const Core::Context& context) noexcept
    {
        LightBuffer result;
        
        for (auto i = 0; i < 4 ; i++)
        {
            result.Positions[i] = context.Lights[i].Position;
            result.Colors[i] = context.Lights[i].Color;
        }

        return result;
    }
}
