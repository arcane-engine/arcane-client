#pragma once

#include <d3d11.h>
#include <wrl/client.h>

#include "Graphics/RenderResource/RenderResource.h"

namespace Graphics
{
    class Device;

    class PixelShader final : public RenderResource
    {
    public:
        explicit PixelShader(const Microsoft::WRL::ComPtr<ID3D11PixelShader>& shader) noexcept;

        void Bind(const Device& device, const RenderContext& renderContext) const noexcept override;

    private:
        Microsoft::WRL::ComPtr<ID3D11PixelShader> _shader;
    };
}
