#pragma once

#include <wrl/client.h>

#include "Graphics/RenderResource/RenderResource.h"

struct ID3D11PixelShader;

namespace Graphics
{
    class PixelShader final : public RenderResource
    {
    public:
        explicit PixelShader(const Microsoft::WRL::ComPtr<ID3D11PixelShader>& pixelShader) noexcept;

        void Bind(Device& device, const RenderContext& renderContext) noexcept override;

    private:
        Microsoft::WRL::ComPtr<ID3D11PixelShader> _pixelShader;
    };
}
