#pragma once

#include <wrl/client.h>

#include "Graphics/RenderResource/RenderResource.h"

struct ID3D11DepthStencilState;

namespace Graphics
{
    class DepthStencilState final : public RenderResource
    {
    public:
        explicit DepthStencilState(const Microsoft::WRL::ComPtr<ID3D11DepthStencilState>& depthStencilState);

        void Bind(Device& device, const RenderContext& renderContext) noexcept override;

    private:
        Microsoft::WRL::ComPtr<ID3D11DepthStencilState> _depthStencilState;
    };
}
