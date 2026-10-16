#pragma once

#include <wrl/client.h>

#include "Graphics/RenderResource/RenderResource.h"

struct ID3D11SamplerState;

namespace Graphics
{
    class Sampler : public RenderResource
    {
    public:
        Sampler(Device& device, const Microsoft::WRL::ComPtr<ID3D11SamplerState>& samplerState, int slot, bool vertexShader, bool pixelShader);

        void Bind(Device& device, const Core::Context& context) noexcept override;

    private:
        Microsoft::WRL::ComPtr<ID3D11SamplerState> _samplerState;
        int _slot;
        bool _vertexShader;
        bool _pixelShader;
    };
}
