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
        explicit PixelShader(const Microsoft::WRL::ComPtr<ID3D11PixelShader>& pixelShader) noexcept;

        void Bind(Device& device, const RenderContext& renderContext) noexcept override;

    private:
        static ID3D11PixelShader* _activePixelShader;
        Microsoft::WRL::ComPtr<ID3D11PixelShader> _pixelShader;
    };
}
