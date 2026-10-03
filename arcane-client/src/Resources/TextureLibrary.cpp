#include "Resources/TextureLibrary.h"

#include <filesystem>
#include <format>

#include "Graphics/Device.h"
#include "Graphics/GraphicsException.h"

namespace Resources
{
    TextureLibrary::TextureLibrary(Graphics::Device& device)
        : _device(device)
    {
        const HRESULT hResult = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&_wicFactory));
        if (FAILED(hResult))
        {
            throw Graphics::GraphicsException("Failed to create WIC imaging factory.", hResult, _device);
        }
    }

    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> TextureLibrary::GetTexture(const std::string& name)
    {
        auto it = _textures.find(name);
        if (it == _textures.end())
        {
            LoadTexture(name);
            it = _textures.find(name);
        }

        return it->second;
    }

    void TextureLibrary::LoadTexture(const std::string& name)
    {
        auto path = std::format(R"(C:\arcane\arcane-data\textures\{}.png)", name);

        Microsoft::WRL::ComPtr<IWICBitmapDecoder> decoder;
        auto hResult = _wicFactory->CreateDecoderFromFilename(std::filesystem::path(path).c_str(), nullptr, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &decoder);
        if (FAILED(hResult))
        {
            throw Graphics::GraphicsException(std::format("Failed to open texture file for '{}'.", path), hResult, _device);
        }

        Microsoft::WRL::ComPtr<IWICBitmapFrameDecode> frame;
        hResult = decoder->GetFrame(0, &frame);
        if (FAILED(hResult))
        {
            throw Graphics::GraphicsException(std::format("Failed to get frame for texture '{}'.", path), hResult, _device);
        }

        Microsoft::WRL::ComPtr<IWICFormatConverter> converter;
        hResult = _wicFactory->CreateFormatConverter(&converter);
        if (FAILED(hResult))
        {
            throw Graphics::GraphicsException(std::format("Failed to create format converter for texture '{}'.", path), hResult, _device);
        }

        hResult = converter->Initialize(frame.Get(), GUID_WICPixelFormat32bppRGBA, WICBitmapDitherTypeNone, nullptr, 0.0, WICBitmapPaletteTypeMedianCut);
        if (FAILED(hResult))
        {
            throw Graphics::GraphicsException(std::format("Failed to convert pixel format for texture '{}'.", path), hResult, _device);
        }

        UINT width = 0;
        UINT height = 0;
        hResult = converter->GetSize(&width, &height);
        if (FAILED(hResult))
        {
            throw Graphics::GraphicsException(std::format("Failed to get size for texture '{}'.", path), hResult, _device);
        }

        const auto stride = width * 4;
        const auto size = stride * height;
        std::vector<BYTE> pixelData(size);

        hResult = converter->CopyPixels(nullptr, stride, size, pixelData.data());
        if (FAILED(hResult))
        {
            throw Graphics::GraphicsException(std::format("Failed to copy pixels for texture '{}'.", path), hResult, _device);
        }

        D3D11_TEXTURE2D_DESC desc = {};
        desc.Width = width;
        desc.Height = height;
        desc.MipLevels = 1;
        desc.ArraySize = 1;
        desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        desc.SampleDesc.Count = 1;
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

        D3D11_SUBRESOURCE_DATA initData = {};
        initData.pSysMem = pixelData.data();
        initData.SysMemPitch = stride;

        Microsoft::WRL::ComPtr<ID3D11Texture2D> texture;
        hResult = _device.GetDevice()->CreateTexture2D(&desc, &initData, &texture);
        if (FAILED(hResult))
        {
            throw Graphics::GraphicsException(std::format("Failed to create texture 2D for '{}'.", name), hResult, _device);
        }

        Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> view;
        hResult = _device.GetDevice()->CreateShaderResourceView(texture.Get(), nullptr, &view);

        if (FAILED(hResult))
        {
            throw Graphics::GraphicsException(std::format("Failed to create shader resource view for '{}'.", name), hResult, _device);
        }

        _textures[name] = view;
    }
}
