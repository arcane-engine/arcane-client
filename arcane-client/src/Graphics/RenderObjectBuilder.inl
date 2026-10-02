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
    inline RenderObjectBuilder::RenderObjectBuilder(Device& device)
        : _device(device)
    {}

    inline RenderObjectBuilder& RenderObjectBuilder::WithVertexShader(const Microsoft::WRL::ComPtr<ID3D11VertexShader>& vertexShader)
    {
        _renderObject.Add(std::make_unique<VertexShader>(vertexShader));

        return *this;
    }

    inline RenderObjectBuilder& RenderObjectBuilder::WithPixelShader(const Microsoft::WRL::ComPtr<ID3D11PixelShader>& pixelShader)
    {
        _renderObject.Add(std::make_unique<PixelShader>(pixelShader));

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
        _renderObject.SetIndexCount(static_cast<UINT>(indexBuffer.size()));
        _renderObject.Add(std::make_unique<IndexBuffer>(_device, indexBuffer));

        return *this;
    }

    inline RenderObjectBuilder& RenderObjectBuilder::WithTopology(D3D11_PRIMITIVE_TOPOLOGY topology)
    {
        _renderObject.Add(std::make_unique<Topology>(topology));

        return *this;
    }

    inline RenderObjectBuilder& RenderObjectBuilder::WithInputLayout(const std::vector<D3D11_INPUT_ELEMENT_DESC>& inputLayout, ID3DBlob* vertexShaderBlob)
    {
        _renderObject.Add(std::make_unique<InputLayout>(_device, inputLayout, vertexShaderBlob));

        return *this;
    }

    inline RenderObjectBuilder& RenderObjectBuilder::WithSampler(D3D11_FILTER filter, D3D11_TEXTURE_ADDRESS_MODE textureAddressMode)
    {
        _renderObject.Add(std::make_unique<Sampler>(_device, filter, textureAddressMode));

        return *this;
    }

    inline RenderObjectBuilder& RenderObjectBuilder::WithTexture(const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& shaderResourceView, Resources::TextureBindingSlot slot)
    {
        _renderObject.Add(std::make_unique<Texture>(shaderResourceView, slot));

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
