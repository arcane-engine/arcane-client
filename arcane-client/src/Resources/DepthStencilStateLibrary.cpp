#include "Resources/DepthStencilStateLibrary.h"

#include "Graphics/Device.h"
#include "Graphics/GraphicsException.h"

namespace Resources
{
    DepthStencilStateLibrary::DepthStencilStateLibrary(const Graphics::Device& device)
    {
        CreateDepthStencilState(device, DepthStencilType::ReadWrite, true, D3D11_DEPTH_WRITE_MASK_ALL, D3D11_COMPARISON_LESS);
        CreateDepthStencilState(device, DepthStencilType::ReadOnly, true, D3D11_DEPTH_WRITE_MASK_ZERO, D3D11_COMPARISON_LESS);
        CreateDepthStencilState(device, DepthStencilType::Disabled, false, D3D11_DEPTH_WRITE_MASK_ZERO, D3D11_COMPARISON_ALWAYS);
    }

    const Microsoft::WRL::ComPtr<ID3D11DepthStencilState>& DepthStencilStateLibrary::GetDepthStencilState(DepthStencilType type) const
    {
        return _states[static_cast<std::size_t>(type)];
    }

    void DepthStencilStateLibrary::CreateDepthStencilState(const Graphics::Device& device, DepthStencilType type, const bool depthEnable, const D3D11_DEPTH_WRITE_MASK depthWriteMask, const D3D11_COMPARISON_FUNC depthFunc)
    {
        CD3D11_DEPTH_STENCIL_DESC desc(D3D11_DEFAULT);
        desc.DepthEnable = depthEnable;
        desc.DepthWriteMask = depthWriteMask;
        desc.DepthFunc = depthFunc;

        device.SetMarker();
        const auto hResult = device.GetDevice()->CreateDepthStencilState(&desc, &_states[static_cast<std::size_t>(type)]);
        if (FAILED(hResult))
        {
            throw Graphics::GraphicsException("Failed to create depth stencil state.", hResult, device.GetDebugMessages());
        }
    }
}
