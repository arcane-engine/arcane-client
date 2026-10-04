#pragma once

#include <d3d11.h>
#include <span>
#include <wrl/client.h>

#include "Graphics/RenderResource/RenderResource.h"

namespace Graphics
{
    class InputLayout final : public RenderResource
    {
    public:
        InputLayout(const Device& device, const std::span<const D3D11_INPUT_ELEMENT_DESC> inputLayout, ID3DBlob* blob);

        void Bind(Device& device, const RenderContext& renderContext) noexcept override;

    private:
        Microsoft::WRL::ComPtr<ID3D11InputLayout> _inputLayout;
    };
}
