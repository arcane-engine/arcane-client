#pragma once

#include <d3d11.h>
#include <string>
#include <unordered_map>
#include <wrl/client.h>

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

        Microsoft::WRL::ComPtr<ID3D11VertexShader> GetVertexShader(const std::string& name);
        ID3DBlob* GetVertexShaderBlob(const std::string& name);
        Microsoft::WRL::ComPtr<ID3D11PixelShader> GetPixelShader(const std::string& name);

    private:
        void LoadVertexShader(const std::string& name);
        void LoadPixelShader(const std::string& name);

        Graphics::Device& _device;

        std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D11VertexShader>> _vertexShaders;
        std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3DBlob>> _vertexShaderBlobs;
        std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D11PixelShader>> _pixelShaders;
    };
}
