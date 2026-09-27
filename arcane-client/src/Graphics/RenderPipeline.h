#pragma once

#include <memory>
#include <vector>

#include "RenderPipeline/RenderNode.h"

namespace Graphics
{
    class Device;
    class RenderQueue;

    class RenderPipeline
    {
    public:
        RenderPipeline() = default;

        void Build(const Device& device);
        void Add(std::unique_ptr<RenderNode> pass);
        void Execute(Device& device, RenderQueue& renderQueue) const;

    private:
        std::vector<std::unique_ptr<RenderNode>> _pipeline;
    };
}
