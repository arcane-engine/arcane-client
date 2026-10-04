#pragma once

#include <d3d11.h>
#include <wrl/client.h>

#include "RenderResource.h"

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
