#include "Sampler.h"

#include "Graphics/Device.h"

namespace Graphics
{
    Sampler::Sampler(Device& device, const Microsoft::WRL::ComPtr<ID3D11SamplerState>& samplerState, const int slot)
        : _slot(slot), _samplerState(samplerState)
    {}

    void Sampler::Bind(Device& device, const RenderContext& renderContext) noexcept
    {
        auto& active = device.GetContextCache().Samplers[_slot];
        auto* target = _samplerState.Get();

        if (target != active)
        {
            device.GetDeviceContext()->PSSetSamplers(_slot, 1, &target);
            active = target;
        }
    }
}
