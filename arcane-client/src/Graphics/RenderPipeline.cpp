#include "RenderPipeline.h"

#include "RenderQueue.h"
#include "Graphics/Device.h"
#include "Graphics/RenderPipeline/BindRenderTarget.h"
#include "Graphics/RenderPipeline/ClearRenderTarget.h"
#include "Graphics/RenderPipeline/Present.h"
#include "Graphics/RenderPipeline/RenderPass.h"
#include "RenderPipeline/ClearDepthStencil.h"
#include "RenderPipeline/CompositeRenderPass.h"
#include "RenderPipeline/GeometryRenderPass.h"
#include "Resources/SamplerLibrary.h"
#include "Resources/ShaderLibrary.h"

namespace Graphics
{
    void RenderPipeline::Build(Device& device, Resources::ShaderLibrary& shaderLibrary, Resources::SamplerLibrary& samplerLibrary, const Resources::DepthStencilStateLibrary& depthStencilStateLibrary)
    {
        _pipeline.clear();

        const auto geometryRenderTarget = device.GetGeometryRenderTarget();
        const auto compositeRenderTarget = device.GetCompositeRenderTarget();
        const auto depthStencil = device.GetDepthStencil();

        Add(std::make_unique<ClearRenderTarget>(geometryRenderTarget));
        Add(std::make_unique<ClearRenderTarget>(compositeRenderTarget));
        Add(std::make_unique<ClearDepthStencil>(depthStencil));
        Add(std::make_unique<BindRenderTarget>(geometryRenderTarget, depthStencil));
        Add(std::make_unique<GeometryRenderPass>());
        Add(std::make_unique<BindRenderTarget>(compositeRenderTarget));
        Add(std::make_unique<CompositeRenderPass>(device, shaderLibrary, samplerLibrary, depthStencilStateLibrary, geometryRenderTarget, depthStencil));
        Add(std::make_unique<Present>());
    }

    void RenderPipeline::Add(std::unique_ptr<RenderPass> pass)
    {
        _pipeline.push_back(std::move(pass));
    }

    void RenderPipeline::Execute(Device& device, RenderQueue& renderQueue, RenderContext& renderContext) const
    {
        for (const auto& pass : _pipeline)
        {
            pass->Execute(device, renderQueue, renderContext);
        }
    }
}
