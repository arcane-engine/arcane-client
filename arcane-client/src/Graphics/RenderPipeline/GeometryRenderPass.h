#pragma once

#include "Graphics/RenderPipeline/RenderPass.h"

namespace Graphics
{
    class GeometryRenderPass : public RenderPass
    {
    public:
        void Execute(Device& device, Core::Context& context) override;
    };
}
