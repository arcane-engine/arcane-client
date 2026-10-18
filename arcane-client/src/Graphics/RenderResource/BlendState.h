#pragma once

#include <wrl/client.h>

#include "Graphics/RenderResource/RenderResource.h"

struct ID3D11BlendState;

namespace Graphics
{
    class BlendState final : public RenderResource
    {
    public:
        explicit BlendState(const Microsoft::WRL::ComPtr<ID3D11BlendState>& blendState);

        void Bind(Device& device, const Core::Context& context) noexcept override;

    private:
        Microsoft::WRL::ComPtr<ID3D11BlendState> _blendState;
    };
}
