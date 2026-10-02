#pragma once

#include <d3d11.h>
#include <string>
#include <unordered_map>
#include <wincodec.h>
#include <wrl/client.h>

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

        Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetTexture(const std::string& name);

    private:
        void LoadTexture(const std::string& name);

        Graphics::Device& _device;
        Microsoft::WRL::ComPtr<IWICImagingFactory> _wicFactory;
        std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> _textures;
    };
}
