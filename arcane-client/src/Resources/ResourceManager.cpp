#include "Resources/ResourceManager.h"

namespace Resources
{
    ResourceManager::ResourceManager(Graphics::Device& device) : 
        _shaderLibrary(device),
        _textureLibrary(device),
        _samplerLibrary(device),
        _depthStencilStateLibrary(device),
        _inputLayoutLibrary(device, _shaderLibrary)
    {}

    ShaderLibrary& ResourceManager::GetShaderLibrary()
    {
        return _shaderLibrary;
    }

    TextureLibrary& ResourceManager::GetTextureLibrary()
    {
        return _textureLibrary;
    }

    MaterialLibrary& ResourceManager::GetMaterialLibrary()
    {
        return _materialLibrary;
    }

    MeshLibrary& ResourceManager::GetMeshLibrary()
    {
        return _meshLibrary;
    }

    SamplerLibrary& ResourceManager::GetSamplerLibrary()
    {
        return _samplerLibrary;
    }

    DepthStencilStateLibrary& ResourceManager::GetDepthStencilStateLibrary()
    {
        return _depthStencilStateLibrary;
    }

    InputLayoutLibrary& ResourceManager::GetInputLayoutLibrary()
    {
        return _inputLayoutLibrary;
    }

    const Microsoft::WRL::ComPtr<ID3D11VertexShader>& ResourceManager::GetVertexShader(const std::string_view name, const bool instanced)
    {
        return _shaderLibrary.GetVertexShader(name, instanced);
    }

    ID3DBlob* ResourceManager::GetVertexShaderBlob(const std::string_view name, const bool instanced)
    {
        return _shaderLibrary.GetVertexShaderBlob(name, instanced);
    }

    const Microsoft::WRL::ComPtr<ID3D11PixelShader>& ResourceManager::GetPixelShader(const std::string_view name)
    {
        return _shaderLibrary.GetPixelShader(name);
    }

    const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& ResourceManager::GetTexture(const std::string_view name)
    {
        return _textureLibrary.GetTexture(name);
    }

    const Material& ResourceManager::GetMaterial(const std::string_view name)
    {
        return _materialLibrary.GetMaterial(name);
    }

    const Mesh& ResourceManager::GetMesh(const std::string_view name)
    {
        return _meshLibrary.GetMesh(name);
    }

    const Microsoft::WRL::ComPtr<ID3D11SamplerState>& ResourceManager::GetSampler(const SamplerType type) const
    {
        return _samplerLibrary.GetSampler(type);
    }

    const Microsoft::WRL::ComPtr<ID3D11DepthStencilState>& ResourceManager::GetDepthStencilState(const DepthStencilStateType type) const
    {
        return _depthStencilStateLibrary.GetDepthStencilState(type);
    }

    const Microsoft::WRL::ComPtr<ID3D11InputLayout>& ResourceManager::GetInputLayout(const InputLayoutType type) const
    {
        return _inputLayoutLibrary.GetInputLayout(type);
    }
}
