#pragma once

#include <d3d11.h>
#include <wrl/client.h>

#include "RenderResource.h"

namespace Graphics
{
    class Sampler : public RenderResource
    {
    public:
        explicit Sampler(Device& device, D3D11_FILTER filter, D3D11_TEXTURE_ADDRESS_MODE textureAddressMode);

        void Bind(const Device& device) const noexcept override;

    private:
        Microsoft::WRL::ComPtr<ID3D11SamplerState> _sampler;
    };
}
