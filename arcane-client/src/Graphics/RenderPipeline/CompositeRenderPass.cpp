#include "CompositeRenderPass.h"

#include <d3d11.h>

#include "Graphics/RenderObject.h"
#include "Graphics/Vertex.h"
#include "Graphics/RenderResource/IndexBuffer.h"
#include "Graphics/RenderResource/InputLayout.h"
#include "Graphics/RenderResource/PixelShader.h"
#include "Graphics/RenderResource/Sampler.h"
#include "Graphics/RenderResource/Texture.h"
#include "Graphics/RenderResource/Topology.h"
#include "Graphics/RenderResource/VertexBuffer.h"
#include "Graphics/RenderResource/VertexShader.h"
#include "Graphics/RenderTarget/RenderTarget.h"
#include "Resources/ShaderLibrary.h"

namespace Graphics
{
    CompositeRenderPass::CompositeRenderPass(Device& device, Resources::ShaderLibrary& shaderLibrary, const std::shared_ptr<RenderTarget>& geometryRenderTarget)
    {
        const std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayout =
        {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
        };

        const std::vector<Vertex> vertexBuffer = {
            { -1.0f,  1.0f, 0.0f,  0.0f, 0.0f },
            {  1.0f,  1.0f, 0.0f,  1.0f, 0.0f },
            { -1.0f, -1.0f, 0.0f,  0.0f, 1.0f },
            {  1.0f, -1.0f, 0.0f,  1.0f, 1.0f }
        };

        std::vector<unsigned int> indexBuffer = {
            0, 1, 2,
            2, 1, 3
        };

        _renderObject.SetIndexCount(static_cast<UINT>(indexBuffer.size()));
        _renderObject.Add(std::make_unique<PixelShader>(shaderLibrary.GetPixelShader("Orthographic")));
        _renderObject.Add(std::make_unique<VertexShader>(shaderLibrary.GetVertexShader("Orthographic")));
        _renderObject.Add(std::make_unique<Sampler>(device, D3D11_FILTER_MIN_MAG_MIP_LINEAR, D3D11_TEXTURE_ADDRESS_CLAMP));
        _renderObject.Add(std::make_unique<Texture>(geometryRenderTarget->GetShaderResourceView(), 0));
        _renderObject.Add(std::make_unique<VertexBuffer>(device, vertexBuffer));
        _renderObject.Add(std::make_unique<IndexBuffer>(device, indexBuffer));
        _renderObject.Add(std::make_unique<Topology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
        _renderObject.Add(std::make_unique<InputLayout>(device, inputLayout, shaderLibrary.GetVertexShaderBlob("Orthographic")));
    }

    void CompositeRenderPass::Execute(Device& device, RenderQueue& renderQueue, RenderContext& renderContext)
    {
        _renderObject.Bind(device, renderContext);
        _renderObject.Draw(device);
    }
}
