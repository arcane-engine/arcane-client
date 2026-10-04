#include "Resources/ShaderLibrary.h"

#include <d3dcompiler.h>
#include <format>

#include "Core/Storage/File.h"
#include "Graphics/Device.h"
#include "Graphics/GraphicsException.h"

namespace Resources
{
    ShaderLibrary::ShaderLibrary(Graphics::Device& device)
        : _device(device)
    {
    }

    const Microsoft::WRL::ComPtr<ID3D11VertexShader>& ShaderLibrary::GetVertexShader(const std::string_view name)
    {
        auto it = _vertexShaders.find(name);
        if (it == _vertexShaders.end())
        {
            LoadVertexShader(name);
            it = _vertexShaders.find(name);
        }

        return it->second;
    }

    ID3DBlob* ShaderLibrary::GetVertexShaderBlob(const std::string_view name)
    {
        auto it = _vertexShaderBlobs.find(name);
        if (it == _vertexShaderBlobs.end())
        {
            LoadVertexShader(name);
            it = _vertexShaderBlobs.find(name);
        }

        return it->second.Get();
    }

    const Microsoft::WRL::ComPtr<ID3D11PixelShader>& ShaderLibrary::GetPixelShader(const std::string_view name)
    {
        auto it = _pixelShaders.find(name);
        if (it == _pixelShaders.end())
        {
            LoadPixelShader(name);
            it = _pixelShaders.find(name);
        }

        return it->second;
    }

    void ShaderLibrary::LoadVertexShader(std::string_view name)
    {
        const auto buffer = Core::File::Read(std::format(R"(C:\arcane\arcane-client\x64\Debug\{}VS.cso)", name));

        _device.SetMarker();
        Microsoft::WRL::ComPtr<ID3DBlob> blob;
        auto hResult = D3DCreateBlob(buffer.size(), &blob);
        if (FAILED(hResult))
        {
            throw Graphics::GraphicsException(std::format("Failed to load vertex shader '{}'.", name), hResult, _device);
        }
        memcpy(blob->GetBufferPointer(), buffer.data(), buffer.size());

        _device.SetMarker();
        Microsoft::WRL::ComPtr<ID3D11VertexShader> shader;
        hResult = _device.GetDevice()->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &shader);
        if (FAILED(hResult))
        {
            throw Graphics::GraphicsException(std::format("Failed to create vertex shader '{}'.", name), hResult, _device);
        }

        _vertexShaders.emplace(name, shader);
        _vertexShaderBlobs.emplace(name, blob);
    }

    void ShaderLibrary::LoadPixelShader(std::string_view name)
    {
        const auto buffer = Core::File::Read(std::format(R"(C:\arcane\arcane-client\x64\Debug\{}PS.cso)", name));

        Microsoft::WRL::ComPtr<ID3D11PixelShader> shader;
        _device.SetMarker();
        const auto hResult = _device.GetDevice()->CreatePixelShader(buffer.data(), buffer.size(), nullptr, &shader);
        if (FAILED(hResult))
        {
            throw Graphics::GraphicsException(std::format("Failed to create pixel shader '{}'.", name), hResult, _device);
        }

        _pixelShaders.emplace(name, shader);
    }
}
