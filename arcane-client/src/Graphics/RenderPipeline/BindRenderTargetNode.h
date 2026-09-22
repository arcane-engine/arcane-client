#pragma once

#include <memory>

#include "Graphics/RenderPipeline/RenderNode.h"
#include "Graphics/RenderTarget/RenderTarget.h"

namespace Graphics
{
    class RenderTarget;

    class BindRenderTargetNode final : public RenderNode
    {
    public:
        explicit BindRenderTargetNode(const std::shared_ptr<RenderTarget>& renderTarget);

        void Execute(Device& device) override;

    private:
        std::shared_ptr<RenderTarget> _renderTarget;
    };
}
