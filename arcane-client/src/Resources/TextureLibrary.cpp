#include "Resources/TextureLibrary.h"

#include <filesystem>
#include <format>

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
}
