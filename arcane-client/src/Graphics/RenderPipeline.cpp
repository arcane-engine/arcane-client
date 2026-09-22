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
        const auto compositeRenderTarget = device.GetCompositeRenderTarget();
        const auto renderTarget = device.GetRenderTarget();

        Add(std::make_unique<ClearBufferNode>(renderTarget));
        Add(std::make_unique<ClearBufferNode>(compositeRenderTarget));
        Add(std::make_unique<BindRenderTargetNode>(renderTarget));
        Add(std::make_unique<BindRenderTargetNode>(compositeRenderTarget));
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
