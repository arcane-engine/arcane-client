#include "Graphics/RenderPipeline/CompositeRenderPass.h"

#include <d3d11.h>

#include "Graphics/RenderObject.h"
#include "Graphics/RenderObjectBuilder.h"
#include "Graphics/Vertex.h"
#include "Graphics/RenderResource/VertexBuffer.h"
#include "Graphics/RenderTarget/DepthStencil.h"
#include "Graphics/RenderTarget/RenderTarget.h"
#include "Resources/DepthStencilStateLibrary.h"
#include "Resources/SamplerLibrary.h"
#include "Resources/ShaderLibrary.h"

namespace Graphics
{
    CompositeRenderPass::CompositeRenderPass(Device& device, Resources::ShaderLibrary& shaderLibrary, Resources::SamplerLibrary& samplerLibrary, const Resources::DepthStencilStateLibrary& depthStencilStateLibrary, const std::shared_ptr<RenderTarget>& geometryRenderTarget, const std::shared_ptr<DepthStencil>& depthStencil)
    {
        constexpr D3D11_INPUT_ELEMENT_DESC inputLayout[] =
        {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
        };

        const std::vector<CompositionVertex> vertexBuffer =
        {
            { -1.0f,  1.0f, 0.0f,  0.0f,  0.0f },
            {  1.0f,  1.0f, 0.0f,  1.0f,  0.0f },
            { -1.0f, -1.0f, 0.0f,  0.0f,  1.0f },
            {  1.0f, -1.0f, 0.0f,  1.0f,  1.0f }
        };

        const unsigned int indexBuffer[] =
        {
            0, 1, 2,
            2, 1, 3
        };

        _renderObject = RenderObjectBuilder(device)
            .WithVertexShader(shaderLibrary.GetVertexShader("Orthographic"))
            .WithPixelShader(shaderLibrary.GetPixelShader("Orthographic"))
            .WithInputLayout(inputLayout, shaderLibrary.GetVertexShaderBlob("Orthographic"))
            .WithDepthStencilState(depthStencilStateLibrary.GetDepthStencilState(Resources::DepthStencilType::Disabled))
            .WithVertexBuffer(vertexBuffer)
            .WithIndexBuffer(indexBuffer)
            .WithTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
            .WithSampler(samplerLibrary.GetSampler(Resources::SamplerType::LinearClamp), 1)
            .WithTexture(geometryRenderTarget->GetShaderResourceView(), Resources::TextureBindingSlot::RenderTarget)
            .WithTexture(depthStencil->GetShaderResourceView(), Resources::TextureBindingSlot::DepthStencil)
            .Build();
    }

    void CompositeRenderPass::Execute(Device& device, [[maybe_unused]] RenderQueue& renderQueue, RenderContext& renderContext)
    {
        _renderObject.Bind(device, renderContext);
        _renderObject.Draw(device);
    }
}
