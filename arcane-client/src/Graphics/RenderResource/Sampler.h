#pragma once

#include <wrl/client.h>

#include "Graphics/RenderResource/RenderResource.h"

struct ID3D11SamplerState;

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
