#pragma once

#include <array>
#include <cstdint>

#include "Graphics/RenderResource/DepthStencilState.h"

namespace Graphics
{
    class Device;
}

namespace Resources
{
    enum class DepthStencilType : std::uint8_t
    {
        ReadWrite,
        ReadOnly,
        Disabled
    };

    class DepthStencilStateLibrary
    {
    public:
        explicit DepthStencilStateLibrary(const Graphics::Device& device);

        [[nodiscard]] const Microsoft::WRL::ComPtr<ID3D11DepthStencilState>& GetDepthStencilState(DepthStencilType type) const;

    private:
        void CreateDepthStencilState(const Graphics::Device& device, DepthStencilType type, bool depthEnable, D3D11_DEPTH_WRITE_MASK depthWriteMask, D3D11_COMPARISON_FUNC depthFunc);

        std::array<Microsoft::WRL::ComPtr<ID3D11DepthStencilState>, 3> _states;
    };
}
