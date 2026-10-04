#pragma once

#include "Graphics/RenderPipeline/RenderPass.h"

namespace Graphics
{
    class GeometryRenderPass : public RenderPass
    {
    public:
        void Execute(Device& device, RenderQueue& renderQueue, RenderContext& renderContext) override;
    };
}
