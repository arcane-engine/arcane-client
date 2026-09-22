#pragma once

#include <d3d11.h>
#include <wrl.h>

#include "Graphics/RenderTarget/RenderBuffer.h"

namespace Graphics
{
    class RenderTarget : public RenderBuffer
    {
    public:
        RenderTarget(Device& device, ID3D11Texture2D* texture);
        RenderTarget(Device& device, int width, int height);

        [[nodiscard]] const Microsoft::WRL::ComPtr<ID3D11RenderTargetView>& GetRenderTargetView() const noexcept;
        [[nodiscard]] const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& GetShaderResourceView() const noexcept;

        void Clear() override;

    private:
        Microsoft::WRL::ComPtr<ID3D11RenderTargetView> _renderTargetView;
        Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> _shaderResourceView;
    };
}
