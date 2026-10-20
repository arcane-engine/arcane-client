#include "Resources/TextureLibrary.h"

#include <filesystem>
#include <format>
#include <fstream>

#include "Core/IO/BinaryReader.h"
#include "Core/IO/FileStream.h"
#include "Graphics/Device.h"
#include "Graphics/GraphicsException.h"
#include "Resources/DDSTextureLoader11.h"

namespace Resources
{
    TextureLibrary::TextureLibrary(Graphics::Device& device)
        : _device(device)
    {}

    const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& TextureLibrary::GetTexture(const std::string_view name)
    {
        auto it = _textures.find(name);
        if (it == _textures.end())
        {
            LoadTexture(name);
            it = _textures.find(name);
        }

        return it->second;
    }

    const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& TextureLibrary::GetHeightmapTexture(const std::string_view name)
    {
        auto it = _textures.find(name);
        if (it == _textures.end())
        {
            LoadHeightmapTexture(name);
            it = _textures.find(name);
        }

        return it->second;
    }

    void TextureLibrary::LoadTexture(std::string_view name)
    {
        auto path = std::format(R"(C:\arcane\arcane-data\textures\{}.dds)", name);

        Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> view;

        const auto hResult = DirectX::CreateDDSTextureFromFile(_device.GetDevice(), std::filesystem::path(path).c_str(), nullptr, view.GetAddressOf() );

        if (FAILED(hResult))
        {
            throw Graphics::GraphicsException(std::format("Failed to load DDS texture for '{}'.", path), hResult, _device.GetDebugMessages());
        }

        _textures.emplace(name, view);
    }

    void TextureLibrary::LoadHeightmapTexture(std::string_view name)
    {
        auto path = std::format(R"(C:\arcane\arcane-data\textures\{}.raw)", name);

        constexpr auto width = 512;
        constexpr auto height = 512;

        auto reader = Core::IO::BinaryReader::FromFile(path);

        const auto heightData = reader.Read<float>(static_cast<std::size_t>(width) * height);

        D3D11_TEXTURE2D_DESC desc = {};
        desc.Width = width;
        desc.Height = height;
        desc.MipLevels = 1;
        desc.ArraySize = 1;
        desc.Format = DXGI_FORMAT_R32_FLOAT;
        desc.SampleDesc.Count = 1;
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

        D3D11_SUBRESOURCE_DATA data = {};
        data.pSysMem = heightData.data();
        data.SysMemPitch = width * sizeof(float);

        Microsoft::WRL::ComPtr<ID3D11Texture2D> texture;
        auto hResult = _device.GetDevice()->CreateTexture2D(&desc, &data, &texture);
        if (FAILED(hResult))
        {
            throw Graphics::GraphicsException(std::format("Failed to create texture 2D for heightmap '{}'.", path), hResult, _device.GetDebugMessages());
        }

        Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> view;
        hResult = _device.GetDevice()->CreateShaderResourceView(texture.Get(), nullptr, view.GetAddressOf());
        if (FAILED(hResult))
        {
            throw Graphics::GraphicsException(std::format("Failed to create SRV for heightmap '{}'.", path), hResult, _device.GetDebugMessages());
        }

        _textures.emplace(name, view);
    }
}
