#include "Sampler.h"

#include "Graphics/Device.h"
#include "Graphics/GraphicsException.h"

namespace Graphics
{
    Sampler::Sampler(Device& device, const D3D11_FILTER filter, const D3D11_TEXTURE_ADDRESS_MODE textureAddressMode)
    {
        CD3D11_SAMPLER_DESC desc(D3D11_DEFAULT);
        desc.Filter = filter;
        desc.AddressU = textureAddressMode;
        desc.AddressV = textureAddressMode;
        desc.AddressW = textureAddressMode;
        desc.MipLODBias = 0.0f;
        desc.MaxAnisotropy = 1;
        desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
        desc.MinLOD = 0;
        desc.MaxLOD = D3D11_FLOAT32_MAX;

        device.SetMarker();
        const auto hResult = device.GetDevice()->CreateSamplerState(&desc, &_sampler);
        if (FAILED(hResult))
        {
            throw GraphicsException("Unable to create sampler state.", hResult, device);
        }
    }

    void Sampler::Bind(Device& device, const RenderContext& renderContext) noexcept
    {
        auto& active = device.GetContextCache().Samplers[0];
        auto* target = _sampler.Get();

        if (target != active)
        {
            device.GetDeviceContext()->PSSetSamplers(0, 1, &target);
            active = target;
        }
    }
}
