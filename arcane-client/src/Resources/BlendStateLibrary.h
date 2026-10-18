#pragma once

#include <array>
#include <cstdint>
#include <d3d11.h>

#include "Graphics/RenderResource/BlendState.h"

namespace Graphics
{
    class Device;
}

namespace Resources
{
    enum class BlendStateType : std::uint8_t
    {
        Opaque,
        Alpha,
    };

    class BlendStateLibrary
    {
    public:
        explicit BlendStateLibrary(const Graphics::Device& device);

        [[nodiscard]] const Microsoft::WRL::ComPtr<ID3D11BlendState>& GetBlendState(BlendStateType type) const;

    private:
        std::array<Microsoft::WRL::ComPtr<ID3D11BlendState>, 2> _states;
    };
}
