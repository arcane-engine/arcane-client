#pragma once

#include <d3d11.h>
#include <wrl/client.h>

namespace Graphics
{
    class Device;

    class RenderTarget
    {
    public:
        RenderTarget(const Device& device, ID3D11Texture2D* texture);
        RenderTarget(const Device& device, int width, int height);

        void Create(const Device& device, ID3D11Texture2D* texture);
        void Create(const Device& device, int width, int height);

        [[nodiscard]] ID3D11RenderTargetView* GetRenderTargetView() const noexcept;
        [[nodiscard]] ID3D11ShaderResourceView* GetShaderResourceView() const noexcept;

        void Clear(const Device& device, float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 0.0f) const;
        void Reset() noexcept;

    private:
        int _width;
        int _height;
        Microsoft::WRL::ComPtr<ID3D11RenderTargetView> _renderTargetView;
        Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> _shaderResourceView;
    };
}
