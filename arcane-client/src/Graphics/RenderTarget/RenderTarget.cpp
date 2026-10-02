#include "Graphics/RenderTarget/RenderTarget.h"

#include "Graphics/Device.h"
#include "Graphics/GraphicsException.h"

namespace Graphics
{
    RenderTarget::RenderTarget(Device& device, ID3D11Texture2D* texture)
    {
        Create(device, texture);
    }

    RenderTarget::RenderTarget(Device& device, const int width, const int height)
        : _width(width), _height(height)
    {
        Create(device, width, height);
    }

    void RenderTarget::Create(Device& device, ID3D11Texture2D* texture)
    {
        D3D11_TEXTURE2D_DESC desc;
        texture->GetDesc(&desc);
        _width = static_cast<int>(desc.Width);
        _height = static_cast<int>(desc.Height);

        device.SetMarker();
        const auto hResult = device.GetDevice()->CreateRenderTargetView(texture, nullptr, &_renderTargetView);
        if (FAILED(hResult))
        {
            throw GraphicsException("Failed to create render target view for back buffer.", hResult, device);
        }
    }

    void RenderTarget::Create(Device& device, const int width, const int height)
    {
        _width = width;
        _height = height;

        //
        // Create render target texture.
        //
        Microsoft::WRL::ComPtr<ID3D11Texture2D> texture;

        D3D11_TEXTURE2D_DESC textureDesc = {};
        textureDesc.Width = static_cast<UINT>(width);
        textureDesc.Height = static_cast<UINT>(height);
        textureDesc.MipLevels = 1;
        textureDesc.ArraySize = 1;
        textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        textureDesc.SampleDesc.Count = 1;
        textureDesc.SampleDesc.Quality = 0;
        textureDesc.Usage = D3D11_USAGE_DEFAULT;
        textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;

        device.SetMarker();
        auto hResult = device.GetDevice()->CreateTexture2D(&textureDesc, nullptr, &texture);
        if (FAILED(hResult))
        {
            throw GraphicsException("Failed to create render target texture.", hResult, device);
        }

        //
        // Create render target view.
        //
        D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
        renderTargetViewDesc.Format = textureDesc.Format;
        renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
        renderTargetViewDesc.Texture2D = D3D11_TEX2D_RTV{};

        device.SetMarker();
        hResult = device.GetDevice()->CreateRenderTargetView(texture.Get(), &renderTargetViewDesc, &_renderTargetView);
        if (FAILED(hResult))
        {
            throw GraphicsException("Failed to create render target view.", hResult, device);
        }

        //
        // Create shader resource view.
        //
        device.SetMarker();
        hResult = device.GetDevice()->CreateShaderResourceView(texture.Get(), nullptr, &_shaderResourceView);
        if (FAILED(hResult))
        {
            throw GraphicsException("Failed to create shader resource view.", hResult, device);
        }
    }

    ID3D11RenderTargetView* RenderTarget::GetRenderTargetView() const noexcept
    {
        return _renderTargetView.Get();
    }

    ID3D11ShaderResourceView* RenderTarget::GetShaderResourceView() const noexcept
    {
        return _shaderResourceView.Get();
    }

    void RenderTarget::Clear(const Device& device, const float r, const float g, const float b, const float a) const
    {
        const float color[] = { r, g, b, a };
        device.GetDeviceContext()->ClearRenderTargetView(_renderTargetView.Get(), color);
    }

    void RenderTarget::Reset() noexcept
    {
        _renderTargetView.Reset();
    }
}
