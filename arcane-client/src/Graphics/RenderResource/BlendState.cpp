#include "Graphics/RenderResource/BlendState.h"

#include "Graphics/Device.h"

namespace Graphics
{
    BlendState::BlendState(const Microsoft::WRL::ComPtr<ID3D11BlendState>& blendState)
        : _blendState(blendState)
    {}

    void BlendState::Bind(Device& device, [[maybe_unused]] const Core::Context& context) noexcept
    {
        auto& active = device.GetContextCache().BlendState;
        auto* target = _blendState.Get();

        if (target != active)
        {
            constexpr float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
            device.GetDeviceContext()->OMSetBlendState(target, blendFactor, 0xFFFFFFFFF);
            active = target;
        }
    }
}
