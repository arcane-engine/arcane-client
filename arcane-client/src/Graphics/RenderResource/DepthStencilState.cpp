#include "Graphics/RenderResource/DepthStencilState.h"

#include "Graphics/Device.h"

namespace Graphics
{
    DepthStencilState::DepthStencilState(const Microsoft::WRL::ComPtr<ID3D11DepthStencilState>& depthStencilState)
        : _depthStencilState(depthStencilState)
    {}

    void DepthStencilState::Bind(Device& device, [[maybe_unused]] const RenderContext& renderContext) noexcept
    {
        auto& active = device.GetContextCache().DepthStencilState;
        auto* target = _depthStencilState.Get();

        if (target != active)
        {
            device.GetDeviceContext()->OMSetDepthStencilState(target, 1);
            active = target;
        }
    }
}
