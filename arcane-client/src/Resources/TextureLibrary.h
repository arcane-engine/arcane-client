#pragma once

#include <d3d11.h>
#include <string>
#include <unordered_map>
#include <wincodec.h>
#include <wrl/client.h>

#include "Core/StringHash.h"

namespace Graphics
{
    class Device;
}

namespace Resources
{
    enum TextureBindingSlot
    {
        Albedo = 0,
        Composition = 0
    };

    class TextureLibrary
    {
    public:
        explicit TextureLibrary(Graphics::Device& device);

        [[nodiscard]] const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& GetTexture(std::string_view name);

    private:
        void LoadTexture(std::string_view name);

        Graphics::Device& _device;
        Microsoft::WRL::ComPtr<IWICImagingFactory> _wicFactory;
        std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>, Core::StringHash, std::equal_to<>> _textures;
    };
}
