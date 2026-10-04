#pragma once

#include <wrl/client.h>

struct ID3D11DepthStencilView;
struct ID3D11ShaderResourceView;

namespace Graphics
{
    class Device;

    class DepthStencil
    {
    public:
        DepthStencil(Device& device, int width, int height);

        void Create(Device& device, int width, int height);

        [[nodiscard]] ID3D11DepthStencilView* GetDepthStencilView() const noexcept;
        [[nodiscard]] ID3D11ShaderResourceView* GetShaderResourceView() const noexcept;

        void Clear(const Device& device) const;
        void Reset() noexcept;

    private:
        int _width;
        int _height;
        Microsoft::WRL::ComPtr<ID3D11DepthStencilView> _depthStencilView;
        Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> _shaderResourceView;
    };
}
