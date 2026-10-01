#pragma once

#include "Graphics/RenderObjectBuilder.h"

#include "Graphics/RenderResource/IndexBuffer.h"
#include "Graphics/RenderResource/InputLayout.h"
#include "Graphics/RenderResource/PixelShader.h"
#include "Graphics/RenderResource/Sampler.h"
#include "Graphics/RenderResource/Texture.h"
#include "Graphics/RenderResource/Topology.h"
#include "Graphics/RenderResource/VertexShader.h"
#include "Resources/ShaderLibrary.h"
#include "Resources/TextureLibrary.h"

namespace Graphics
{
    inline RenderObjectBuilder::RenderObjectBuilder(Device& device, Resources::ShaderLibrary* shaderLibrary, Resources::TextureLibrary* textureLibrary)
        : _device(device), _shaderLibrary(shaderLibrary), _textureLibrary(textureLibrary)
    {}

    inline RenderObjectBuilder& RenderObjectBuilder::WithVertexShader(const std::string& vertexShaderName)
    {
        _renderObject.Add(std::make_unique<VertexShader>(_shaderLibrary->GetVertexShader(vertexShaderName)));

        return *this;
    }

    inline RenderObjectBuilder& RenderObjectBuilder::WithPixelShader(const std::string& vertexShaderName)
    {
        _renderObject.Add(std::make_unique<PixelShader>(_shaderLibrary->GetPixelShader(vertexShaderName)));

        return *this;
    }

    inline RenderObjectBuilder& RenderObjectBuilder::WithInputLayout(const std::vector<D3D11_INPUT_ELEMENT_DESC>& inputLayout, const std::string& vertexShaderName)
    {
        _renderObject.Add(std::make_unique<InputLayout>(_device, inputLayout, _shaderLibrary->GetVertexShaderBlob(vertexShaderName)));

        return *this;
    }

    template <typename T>
    RenderObjectBuilder& RenderObjectBuilder::WithVertexBuffer(const std::vector<T>& vertices)
    {
        _renderObject.Add(std::make_unique<VertexBuffer>(_device, vertices));

        return *this;
    }

    inline RenderObjectBuilder& RenderObjectBuilder::WithIndexBuffer(const std::vector<unsigned int>& indexBuffer)
    {
        _renderObject.SetIndexCount(indexBuffer.size());
        _renderObject.Add(std::make_unique<IndexBuffer>(_device, indexBuffer));

        return *this;
    }

    inline RenderObjectBuilder& RenderObjectBuilder::WithTopology(D3D11_PRIMITIVE_TOPOLOGY topology)
    {
        _renderObject.Add(std::make_unique<Topology>(topology));

        return *this;
    }

    inline RenderObjectBuilder& RenderObjectBuilder::WithSampler(D3D11_FILTER filter, D3D11_TEXTURE_ADDRESS_MODE textureAddressMode)
    {
        _renderObject.Add(std::make_unique<Sampler>(_device, filter, textureAddressMode));

        return *this;
    }

    inline RenderObjectBuilder& RenderObjectBuilder::WithTexture(const std::string& textureName, Resources::TextureBindingSlot slot)
    {
        _renderObject.Add(std::make_unique<Texture>(_textureLibrary->GetTexture(textureName), slot));

        return *this;
    }

    template<typename T>
    RenderObjectBuilder& RenderObjectBuilder::WithConstantBuffer(UINT slot, bool vertexShader, bool pixelShader)
    {
        _renderObject.Add(std::make_unique<ConstantBuffer<T>>(_device, slot, vertexShader, pixelShader));

        return *this;
    }

    inline RenderObject RenderObjectBuilder::Build()
    {
        return std::move(_renderObject);
    }
}
