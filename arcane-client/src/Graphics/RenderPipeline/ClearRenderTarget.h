#pragma once

#include <memory>

#include "Graphics/RenderPipeline/RenderPass.h"

namespace Graphics
{
    class RenderTarget;

    class ClearRenderTarget final : public RenderPass
    {
    public:
        explicit ClearRenderTarget(const std::shared_ptr<RenderTarget>& renderTarget);

        void Execute(Device& device, RenderQueue& renderQueue, RenderContext& renderContext) override;

    private:
        std::shared_ptr<RenderTarget> _renderTarget;
    };
}
