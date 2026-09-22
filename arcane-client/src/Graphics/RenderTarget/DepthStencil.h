#pragma once

#include <d3d11.h>
#include <wrl.h>

#include "Graphics/RenderTarget/RenderBuffer.h"

namespace Graphics
{
    class DepthStencil : public RenderBuffer
    {
    public:
        DepthStencil(Device& device, int width, int height);

        [[nodiscard]] ID3D11DepthStencilView* GetDepthStencilView() const noexcept;
        [[nodiscard]] ID3D11ShaderResourceView* GetShaderResourceView() const noexcept;

        void Clear() override;

    private:
        Microsoft::WRL::ComPtr<ID3D11DepthStencilState> _depthStencilState;
        Microsoft::WRL::ComPtr<ID3D11DepthStencilView> _depthStencilView;
        Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> _shaderResourceView;
    };
}
