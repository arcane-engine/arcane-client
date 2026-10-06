#pragma once

#include <memory>
#include <vector>

#include "Graphics/RenderPipeline/RenderPass.h"

namespace Resources
{
    class InputLayoutLibrary;
    class DepthStencilStateLibrary;
    class SamplerLibrary;
    class ShaderLibrary;
}

namespace Graphics
{
    class RenderPipeline
    {
    public:
        RenderPipeline() = default;

        void Build(Device& device, Resources::ShaderLibrary& shaderLibrary, Resources::SamplerLibrary& samplerLibrary, const Resources::DepthStencilStateLibrary& depthStencilStateLibrary, Resources::InputLayoutLibrary& inputLayoutLibrary);
        void Add(std::unique_ptr<RenderPass> pass);
        void Execute(Device& device, RenderQueue& renderQueue, RenderContext& renderContext) const;

    private:
        std::vector<std::unique_ptr<RenderPass>> _pipeline;
    };
}
