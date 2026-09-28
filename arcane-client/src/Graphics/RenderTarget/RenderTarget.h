#pragma once

#include <d3d11.h>
#include <wrl/client.h>

namespace Graphics
{
    class Device;

    class RenderTarget
    {
    public:
        RenderTarget(Device& device, ID3D11Texture2D* texture);
        RenderTarget(Device& device, int width, int height);

        [[nodiscard]] ID3D11RenderTargetView* GetRenderTargetView() const noexcept;
        [[nodiscard]] ID3D11ShaderResourceView* GetShaderResourceView() const noexcept;

        void Clear(const Device& device) const;

    private:
        int _width;
        int _height;
        Microsoft::WRL::ComPtr<ID3D11RenderTargetView> _renderTargetView;
        Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> _shaderResourceView;
    };
}
