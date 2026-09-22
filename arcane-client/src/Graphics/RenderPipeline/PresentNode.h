#pragma once

#include "Graphics/RenderPipeline/RenderNode.h"

namespace Graphics
{
    class PresentNode final : public RenderNode
    {
    public:
        void Execute(Device& device) override;
    };
}
