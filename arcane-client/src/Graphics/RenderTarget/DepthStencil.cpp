#include "Graphics/RenderTarget/DepthStencil.h"

#include "Graphics/Device.h"
#include "Graphics/GraphicsException.h"

namespace Graphics
{
    DepthStencil::DepthStencil(Device& device, int width, int height)
        : RenderBuffer(device, width, height)
    {
        //
        // Create and set depth stencil state.
        //
        D3D11_DEPTH_STENCIL_DESC depthStencilDesc = {};
        depthStencilDesc.DepthEnable = true;
        depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
        depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

        _device.SetDebugMarker();
        auto hResult = _device.GetDevice()->CreateDepthStencilState(&depthStencilDesc, &_depthStencilState);
        if (FAILED(hResult))
        {
            throw GraphicsException("Failed to create depth stencil state.", hResult, _device);
        }

        _device.GetDeviceContext()->OMSetDepthStencilState(_depthStencilState.Get(), 0);

        //
        // Create depth stencil texture.
        //
        Microsoft::WRL::ComPtr<ID3D11Texture2D> depthStencilTexture;

        D3D11_TEXTURE2D_DESC textureDesc = {};
        textureDesc.Width = width;
        textureDesc.Height = height;
        textureDesc.MipLevels = 1;
        textureDesc.ArraySize = 1;
        textureDesc.Format = DXGI_FORMAT_R32_TYPELESS;
        textureDesc.SampleDesc.Count = 1;
        textureDesc.SampleDesc.Quality = 0;
        textureDesc.Usage = D3D11_USAGE_DEFAULT;
        textureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;

        _device.SetDebugMarker();
        hResult = _device.GetDevice()->CreateTexture2D(&textureDesc, nullptr, &depthStencilTexture);
        if (FAILED(hResult))
        {
            throw GraphicsException("Failed to create texture.", hResult, _device);
        }

        //
        // Create depth stencil view.
        //
        D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc = {};
        depthStencilViewDesc.Format = DXGI_FORMAT_D32_FLOAT;
        depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
        depthStencilViewDesc.Texture2D.MipSlice = 0;

        _device.SetDebugMarker();
        hResult = _device.GetDevice()->CreateDepthStencilView(depthStencilTexture.Get(), &depthStencilViewDesc, &_depthStencilView);
        if (FAILED(hResult))
        {
            throw GraphicsException("Failed to create depth stencil view.", hResult, _device);
        }

        //
        // Create shader resource view.
        //
        D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc = {};
        shaderResourceViewDesc.Format = DXGI_FORMAT_R32_FLOAT;
        shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
        shaderResourceViewDesc.Texture2D.MipLevels = 1;

        _device.SetDebugMarker();
        hResult = _device.GetDevice()->CreateShaderResourceView(depthStencilTexture.Get(), &shaderResourceViewDesc, &_shaderResourceView);
        if (FAILED(hResult))
        {
            throw GraphicsException("Failed to create shader resource view.", hResult, _device);
        }
    }

    ID3D11DepthStencilView* DepthStencil::GetDepthStencilView() const noexcept
    {
        return _depthStencilView.Get();
    }

    ID3D11ShaderResourceView* DepthStencil::GetShaderResourceView() const noexcept
    {
        return _shaderResourceView.Get();
    }

    void DepthStencil::Clear()
    {
        _device.GetDeviceContext()->ClearDepthStencilView(_depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    }
}
