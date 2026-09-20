#include "Graphics/Buffer/RenderTarget.h"

#include "Graphics/Device.h"
#include "Graphics/GraphicsException.h"

namespace
{
    constexpr float ClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
}

namespace Graphics::Buffer
{
    RenderTarget::RenderTarget(Device& device, ID3D11Texture2D* texture)
        : RenderBuffer(device, 0, 0)
    {
        if (texture != nullptr)
        {
            D3D11_TEXTURE2D_DESC desc;
            texture->GetDesc(&desc);
            _width = static_cast<int>(desc.Width);
            _height = static_cast<int>(desc.Height);
        }

        _device.SetMarker();
        const auto hResult = _device.GetDevice()->CreateRenderTargetView(texture, nullptr, &_renderTargetView);
        if (FAILED(hResult))
        {
            throw GraphicsException("Failed to create render target view for back buffer.", hResult, _device);
        }
    }

    RenderTarget::RenderTarget(Device& device, const int width, const int height)
        : RenderBuffer(device, width, height)
    {
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

        _device.SetMarker();
        auto hResult = _device.GetDevice()->CreateTexture2D(&textureDesc, nullptr, &texture);
        if (FAILED(hResult))
        {
            throw GraphicsException("Failed to create render target texture.", hResult, _device);
        }

        D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
        renderTargetViewDesc.Format = textureDesc.Format;
        renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
        renderTargetViewDesc.Texture2D = D3D11_TEX2D_RTV{};

        _device.SetMarker();
        hResult = _device.GetDevice()->CreateRenderTargetView(texture.Get(), &renderTargetViewDesc, &_renderTargetView);
        if (FAILED(hResult))
        {
            throw GraphicsException("Failed to create render target view.", hResult, _device);
        }

        _device.SetMarker();
        hResult = _device.GetDevice()->CreateShaderResourceView(texture.Get(), nullptr, &_shaderResourceView);
        if (FAILED(hResult))
        {
            throw GraphicsException("Failed to create shader resource view.", hResult, _device);
        }
    }

    const Microsoft::WRL::ComPtr<ID3D11RenderTargetView>& RenderTarget::GetRenderTargetView() const noexcept
    {
        return _renderTargetView;
    }

    const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& RenderTarget::GetShaderResourceView() const noexcept
    {
        return _shaderResourceView;
    }

    void RenderTarget::Clear()
    {
        _device.GetDeviceContext()->ClearRenderTargetView(_renderTargetView.Get(), ClearColor);
    }
}