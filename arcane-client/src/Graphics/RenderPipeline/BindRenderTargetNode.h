#pragma once

#include <memory>

#include "Graphics/RenderPipeline/RenderNode.h"
#include "Graphics/RenderTarget/RenderTarget.h"

namespace Graphics
{
    class DepthStencil;
    class RenderTarget;

    class BindRenderTargetNode final : public RenderNode
    {
    public:
        explicit BindRenderTargetNode(const std::shared_ptr<RenderTarget>& renderTarget, const std::shared_ptr<DepthStencil>& depthStencil = nullptr);

        void Execute(Device& device, RenderQueue& renderQueue) override;

    private:
        std::shared_ptr<RenderTarget> _renderTarget;
        std::shared_ptr<DepthStencil> _depthStencil;
    };
}
