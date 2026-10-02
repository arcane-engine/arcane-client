#pragma once

#include <d3d11.h>
#include <vector>
#include <wrl/client.h>

#include "Graphics/RenderResource/RenderResource.h"

namespace Graphics
{
    class Device;

    class InputLayout final : public RenderResource
    {
    public:
        InputLayout(Device& device, const std::vector<D3D11_INPUT_ELEMENT_DESC>& inputLayout, ID3DBlob* blob);

        void Bind(Device& device, const RenderContext& renderContext) noexcept override;

    private:
        Microsoft::WRL::ComPtr<ID3D11InputLayout> _inputLayout;
    };
}
