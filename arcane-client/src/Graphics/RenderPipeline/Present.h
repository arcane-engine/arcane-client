#pragma once

#include "Graphics/RenderPipeline/RenderPass.h"

namespace Graphics
{
    class Present final : public RenderPass
    {
    public:
        void Execute(Device& device, RenderQueue& renderQueue, RenderContext& renderContext) override;
    };
}
