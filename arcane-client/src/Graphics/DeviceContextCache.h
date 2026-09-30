#pragma once

#include <array>
#include <d3d11.h>

namespace Graphics
{
    struct DeviceContextCache
    {
        ID3D11PixelShader* PixelShader;
        ID3D11VertexShader* VertexShader;
        ID3D11InputLayout* InputLayout;
        ID3D11Buffer* IndexBuffer;
        ID3D11Buffer* VertexBuffer;
        std::array<ID3D11Buffer*, 4> VertexShaderConstantBuffers{};
        std::array<ID3D11Buffer*, 4> PixelShaderConstantBuffers{};
        std::array<ID3D11SamplerState*, 4> Samplers{};
        std::array<ID3D11ShaderResourceView*, 8> Textures{};
        D3D11_PRIMITIVE_TOPOLOGY Topology = D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED;

        DeviceContextCache();
    };
}
