#pragma once

#include "Device.h"
#include "RenderObject.h"
#include "RenderResource/ConstantBuffer.h"
#include "RenderResource/VertexBuffer.h"
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
        explicit RenderObjectBuilder(Device& device, Resources::ShaderLibrary* shaderLibrary = nullptr, Resources::TextureLibrary* textureLibrary = nullptr);

        // Shaders & Layout
        [[nodiscard]] RenderObjectBuilder& WithVertexShader(const std::string& vertexShaderName);
        [[nodiscard]] RenderObjectBuilder& WithPixelShader(const std::string& vertexShaderName);
        [[nodiscard]] RenderObjectBuilder& WithInputLayout(const std::vector<D3D11_INPUT_ELEMENT_DESC>& inputLayout, const std::string& vertexShaderName);

        // Geometry & Input Assembly
        template<typename T>
        [[nodiscard]] RenderObjectBuilder& WithVertexBuffer(const std::vector<T>& vertices);
        [[nodiscard]] RenderObjectBuilder& WithIndexBuffer(const std::vector<unsigned int>& indexBuffer);
        [[nodiscard]] RenderObjectBuilder& WithTopology(D3D11_PRIMITIVE_TOPOLOGY topology);

        // Textures & Samplers
        [[nodiscard]] RenderObjectBuilder& WithTexture(const std::string& textureName, Resources::TextureBindingSlot slot);
        [[nodiscard]] RenderObjectBuilder& WithSampler(D3D11_FILTER filter, D3D11_TEXTURE_ADDRESS_MODE textureAddressMode);

        // Constant Buffers
        template<typename T>
        [[nodiscard]] RenderObjectBuilder& WithConstantBuffer(UINT slot = 1, bool vertexShader = true, bool pixelShader = false);

        [[nodiscard]] RenderObject Build();

    private:
        RenderObject _renderObject;
        Device& _device;
        Resources::ShaderLibrary* _shaderLibrary;
        Resources::TextureLibrary* _textureLibrary;
    };
}

#include "Graphics/RenderObjectBuilder.inl"
