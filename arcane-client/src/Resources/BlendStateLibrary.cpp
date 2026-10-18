#include "Resources/BlendStateLibrary.h"

#include "Graphics/Device.h"
#include "Graphics/GraphicsException.h"

namespace Resources
{
    BlendStateLibrary::BlendStateLibrary(const Graphics::Device& device)
    {
        CD3D11_BLEND_DESC desc(D3D11_DEFAULT);
        desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

        desc.RenderTarget[0].BlendEnable = FALSE;
        auto hResult = device.GetDevice()->CreateBlendState(&desc, &_states[0]);
        if (FAILED(hResult)) {
            throw Graphics::GraphicsException("Failed to create blend state.", hResult, device.GetDebugMessages());
        }

        desc.RenderTarget[0].BlendEnable = TRUE;
        desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
        desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
        desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
        desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
        desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
        desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
        hResult = device.GetDevice()->CreateBlendState(&desc, &_states[1]);
        if (FAILED(hResult)) {
            throw Graphics::GraphicsException("Failed to create blend state.", hResult, device.GetDebugMessages());
        }
    }

    const Microsoft::WRL::ComPtr<ID3D11BlendState>& BlendStateLibrary::GetBlendState(BlendStateType type) const
    {
        return _states[static_cast<std::size_t>(type)];
    }
}
