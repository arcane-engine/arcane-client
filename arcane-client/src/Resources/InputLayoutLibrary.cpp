#include "InputLayoutLibrary.h"

#include "ShaderLibrary.h"
#include "Graphics/Device.h"
#include "Graphics/GraphicsException.h"

namespace Resources
{
    InputLayoutLibrary::InputLayoutLibrary(const Graphics::Device& device, ShaderLibrary& shaderLibrary)
    {
        constexpr D3D11_INPUT_ELEMENT_DESC positionTexture[] =
        {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
        };

        CreateInputLayout(device, InputLayoutType::PositionTexture, positionTexture, shaderLibrary.GetVertexShaderBlob("PositionTextureLayout"));

        constexpr D3D11_INPUT_ELEMENT_DESC positionNormalTexture[] =
        {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 }
        };

        CreateInputLayout(device, InputLayoutType::PositionNormalTexture, positionNormalTexture, shaderLibrary.GetVertexShaderBlob("PositionNormalTextureLayout"));

        constexpr D3D11_INPUT_ELEMENT_DESC positionNormalTextureInstanced[] =
        {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "INSTANCE_MATRIX", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 0,  D3D11_INPUT_PER_INSTANCE_DATA, 1 },
            { "INSTANCE_MATRIX", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 16, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
            { "INSTANCE_MATRIX", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 32, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
            { "INSTANCE_MATRIX", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 48, D3D11_INPUT_PER_INSTANCE_DATA, 1 }
        };

        CreateInputLayout(device, InputLayoutType::PositionNormalTextureInstanced, positionNormalTextureInstanced, shaderLibrary.GetVertexShaderBlob("PositionNormalTextureLayout", true));
    }

    const Microsoft::WRL::ComPtr<ID3D11InputLayout>& InputLayoutLibrary::GetInputLayout(InputLayoutType type)
    {
        return _inputLayouts[static_cast<int>(type)];
    }

    void InputLayoutLibrary::CreateInputLayout(const Graphics::Device& device, InputLayoutType type, const std::span<const D3D11_INPUT_ELEMENT_DESC> inputLayout, ID3DBlob* vertexShaderBlob)
    {
        device.SetMarker();
        const auto hResult = device.GetDevice()->CreateInputLayout(inputLayout.data(), static_cast<UINT>(inputLayout.size()), vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), &_inputLayouts[static_cast<int>(type)]);
        if (FAILED(hResult))
        {
            throw Graphics::GraphicsException("Unable to create input layout.", hResult, device.GetDebugMessages());
        }
    }
}
