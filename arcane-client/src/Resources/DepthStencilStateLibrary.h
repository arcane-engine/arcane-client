#pragma once

#include <array>
#include <cstdint>
#include <d3d11.h>

#include "Graphics/RenderResource/DepthStencilState.h"

namespace Graphics
{
    class Device;
}

namespace Resources
{
    enum class DepthStencilStateType : std::uint8_t
    {
        Read,
        Write,
        Disabled
    };

    class DepthStencilStateLibrary
    {
    public:
        explicit DepthStencilStateLibrary(const Graphics::Device& device);

        [[nodiscard]] const Microsoft::WRL::ComPtr<ID3D11DepthStencilState>& GetDepthStencilState(DepthStencilStateType type) const;

    private:
        void CreateDepthStencilState(const Graphics::Device& device, DepthStencilStateType type, bool depthEnable, D3D11_DEPTH_WRITE_MASK depthWriteMask, D3D11_COMPARISON_FUNC depthFunc);

        std::array<Microsoft::WRL::ComPtr<ID3D11DepthStencilState>, 3> _states;
    };
}
