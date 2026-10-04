#pragma once

#include <memory>
#include <vector>

#include "RenderPipeline/RenderPass.h"

namespace Resources
{
    class DepthStencilStateLibrary;
    class SamplerLibrary;
    class ShaderLibrary;
}

namespace Graphics
{
    class RenderContext;
    class Device;
    class RenderQueue;

    class RenderPipeline
    {
    public:
        RenderPipeline() = default;

        void Build(Device& device, Resources::ShaderLibrary& shaderLibrary, Resources::SamplerLibrary& samplerLibrary, const Resources::DepthStencilStateLibrary& depthStencilStateLibrary);
        void Add(std::unique_ptr<RenderPass> pass);
        void Execute(Device& device, RenderQueue& renderQueue, RenderContext& renderContext) const;

    private:
        std::vector<std::unique_ptr<RenderPass>> _pipeline;
    };
}
