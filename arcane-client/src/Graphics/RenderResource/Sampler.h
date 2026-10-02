#pragma once

#include <d3d11.h>
#include <wrl/client.h>

#include "RenderResource.h"

namespace Graphics
{
    class Sampler : public RenderResource
    {
    public:
        explicit Sampler(Device& device, const Microsoft::WRL::ComPtr<ID3D11SamplerState>& samplerState, int slot);

        void Bind(Device& device, const RenderContext& renderContext) noexcept override;

    private:
        int _slot;
        Microsoft::WRL::ComPtr<ID3D11SamplerState> _samplerState;
    };
}
