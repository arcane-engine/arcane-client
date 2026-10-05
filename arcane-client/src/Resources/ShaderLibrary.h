#pragma once

#include <d3d11.h>
#include <string>
#include <unordered_map>
#include <wrl/client.h>

#include "Core/Common/StringHash.h"

namespace Graphics
{
    class Device;
}

namespace Resources
{
    class ShaderLibrary
    {
    public:
        explicit ShaderLibrary(Graphics::Device& device);

        [[nodiscard]] const Microsoft::WRL::ComPtr<ID3D11VertexShader>& GetVertexShader(std::string_view name, bool instanced = false);
        [[nodiscard]] ID3DBlob* GetVertexShaderBlob(std::string_view name, bool instanced = false);
        [[nodiscard]] const Microsoft::WRL::ComPtr<ID3D11PixelShader>& GetPixelShader(std::string_view name);

    private:
        void LoadVertexShader(std::string_view name);
        void LoadPixelShader(std::string_view name);

        Graphics::Device& _device;

        std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D11VertexShader>, Core::StringHash, std::equal_to<>> _vertexShaders;
        std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3DBlob>, Core::StringHash, std::equal_to<>> _vertexShaderBlobs;
        std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D11PixelShader>, Core::StringHash, std::equal_to<>> _pixelShaders;
    };
}
