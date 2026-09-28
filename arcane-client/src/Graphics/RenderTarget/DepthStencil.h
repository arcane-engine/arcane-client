#pragma once

#include <d3d11.h>
#include <wrl/client.h>

namespace Graphics
{
    class Device;

    class DepthStencil
    {
    public:
        DepthStencil(Device& device, int width, int height);

        [[nodiscard]] ID3D11DepthStencilView* GetDepthStencilView() const noexcept;
        [[nodiscard]] ID3D11ShaderResourceView* GetShaderResourceView() const noexcept;

        void Clear(const Device& device) const;

    private:
        int _width;
        int _height;
        Microsoft::WRL::ComPtr<ID3D11DepthStencilState> _depthStencilState;
        Microsoft::WRL::ComPtr<ID3D11DepthStencilView> _depthStencilView;
        Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> _shaderResourceView;
    };
}
