#pragma once

#include "RenderNode.h"

namespace Graphics
{
    class GeometryPassNode : public RenderNode
    {
    public:
        void Execute(Device& device, RenderQueue& renderQueue) override;
    };
}
