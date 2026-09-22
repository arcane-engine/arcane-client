#include "RenderPipeline.h"

#include "Graphics/Device.h"
#include "Graphics/RenderPipeline/BindRenderTargetNode.h"
#include "Graphics/RenderPipeline/ClearBufferNode.h"
#include "Graphics/RenderPipeline/PresentNode.h"
#include "Graphics/RenderPipeline/RenderNode.h"

namespace Graphics
{
    void RenderPipeline::Build(const Device& device)
    {
        const auto sceneRenderTarget = device.GetSceneRenderTarget();
        const auto outputRenderTarget = device.GetOutputRenderTarget();
        const auto depthStencil = device.GetDepthStencil();

        Add(std::make_unique<ClearBufferNode>(sceneRenderTarget));
        Add(std::make_unique<ClearBufferNode>(outputRenderTarget));

        Add(std::make_unique<BindRenderTargetNode>(sceneRenderTarget, depthStencil));
        Add(std::make_unique<BindRenderTargetNode>(outputRenderTarget));

        Add(std::make_unique<PresentNode>());
    }

    void RenderPipeline::Add(std::unique_ptr<RenderNode> pass)
    {
        _pipeline.push_back(std::move(pass));
    }

    void RenderPipeline::Execute(Device& device) const
    {
        for (const auto& pass : _pipeline)
        {
            pass->Execute(device);
        }
    }
}
