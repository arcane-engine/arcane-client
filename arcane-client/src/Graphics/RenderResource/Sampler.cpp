#include "Graphics/RenderResource/Sampler.h"

#include "Graphics/Device.h"

namespace Graphics
{
    Sampler::Sampler([[maybe_unused]] Device& device, const Microsoft::WRL::ComPtr<ID3D11SamplerState>& samplerState, const int slot, const bool vertexShader, const bool pixelShader)
        : _samplerState(samplerState), _slot(slot), _vertexShader(vertexShader), _pixelShader(pixelShader)
    {
    }

    void Sampler::Bind(Device& device, [[maybe_unused]] const Core::Context& context) noexcept
    {
        auto* target = _samplerState.Get();

        if (_vertexShader)
        {
            auto& active = device.GetContextCache().VertexShaderSamplers[_slot];
            if (target != active)
            {
                device.GetDeviceContext()->VSSetSamplers(_slot, 1, &target);
                active = target;
            }
        }
        if (_pixelShader)
        {
            auto& active = device.GetContextCache().PixelShaderSamplers[_slot];
            if (target != active)
            {
                device.GetDeviceContext()->PSSetSamplers(_slot, 1, &target);
                active = target;
            }
        }
    }
}
