#pragma once

#include "Graphics/Device.h"
#include "Graphics/RenderObject.h"
#include "Graphics/RenderResource/ConstantBuffer.h"
#include "Graphics/RenderResource/VertexBuffer.h"
#include "Resources/TextureLibrary.h"

namespace Resources
{
    class TextureLibrary;
    class ShaderLibrary;
}

namespace Graphics
{
    class RenderObjectBuilder
    {
    public:
        explicit RenderObjectBuilder(Device& device);

        // Shaders & Layout
        [[nodiscard]] RenderObjectBuilder& WithVertexShader(const Microsoft::WRL::ComPtr<ID3D11VertexShader>& vertexShader);
        [[nodiscard]] RenderObjectBuilder& WithPixelShader(const Microsoft::WRL::ComPtr<ID3D11PixelShader>& pixelShader);

        // Geometry & Input Assembly
        template<typename T>
        [[nodiscard]] RenderObjectBuilder& WithVertexBuffer(const std::vector<T>& vertices);
        [[nodiscard]] RenderObjectBuilder& WithIndexBuffer(const std::vector<unsigned int>& indexBuffer);
        [[nodiscard]] RenderObjectBuilder& WithTopology(D3D11_PRIMITIVE_TOPOLOGY topology);
        [[nodiscard]] RenderObjectBuilder& WithInputLayout(const std::vector<D3D11_INPUT_ELEMENT_DESC>& inputLayout, ID3DBlob* vertexShaderBlob);

        // Textures & Samplers
        [[nodiscard]] RenderObjectBuilder& WithTexture(const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& shaderResourceView, Resources::TextureBindingSlot slot);
        [[nodiscard]] RenderObjectBuilder& WithSampler(const Microsoft::WRL::ComPtr<ID3D11SamplerState>& samplerState, int slot);

        // Constant Buffers
        template<typename T>
        [[nodiscard]] RenderObjectBuilder& WithConstantBuffer(UINT slot = 1, bool vertexShader = true, bool pixelShader = false);

        // Pipeline States
        [[nodiscard]] RenderObjectBuilder& WithDepthStencilState(const Microsoft::WRL::ComPtr<ID3D11DepthStencilState>& depthStencilState);

        [[nodiscard]] RenderObject Build();

    private:
        RenderObject _renderObject;
        Device& _device;
    };
}

#include "Graphics/RenderObjectBuilder.inl"
