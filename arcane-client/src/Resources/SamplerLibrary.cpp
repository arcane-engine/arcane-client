#include "Resources/SamplerLibrary.h"

#include "Graphics/Device.h"
#include "Graphics/GraphicsException.h"

namespace Resources
{
    SamplerLibrary::SamplerLibrary(Graphics::Device& device)
        : _device(device)
    {
        CreateSampler(SamplerType::LinearWrap, D3D11_FILTER_MIN_MAG_MIP_LINEAR, D3D11_TEXTURE_ADDRESS_WRAP);
        CreateSampler(SamplerType::LinearClamp, D3D11_FILTER_MIN_MAG_MIP_LINEAR, D3D11_TEXTURE_ADDRESS_CLAMP);
    }

    const Microsoft::WRL::ComPtr<ID3D11SamplerState>& SamplerLibrary::GetSampler(const SamplerType type)
    {
        return _samplers[static_cast<size_t>(type)];
    }

    void SamplerLibrary::CreateSampler(const SamplerType type, const D3D11_FILTER filter, const D3D11_TEXTURE_ADDRESS_MODE address)
    {
        CD3D11_SAMPLER_DESC desc(D3D11_DEFAULT);
        desc.Filter = filter;
        desc.AddressU = address;
        desc.AddressV = address;
        desc.AddressW = address;
        desc.MipLODBias = 0.0f;
        desc.MaxAnisotropy = 1;
        desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
        desc.MinLOD = 0;
        desc.MaxLOD = D3D11_FLOAT32_MAX;

        _device.SetMarker();
        Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState;
        const auto hResult = _device.GetDevice()->CreateSamplerState(&desc, samplerState.GetAddressOf());
        if (FAILED(hResult))
        {
            throw Graphics::GraphicsException("Unable to create sampler state.", hResult, _device.GetDebugMessages());
        }

        _samplers[static_cast<size_t>(type)] = std::move(samplerState);
    }
}
