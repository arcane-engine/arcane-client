#pragma once

#include "Graphics/RenderObject.h"
#include "Graphics/RenderPipeline/RenderPass.h"

namespace Resources
{
    class SamplerLibrary;
    class ShaderLibrary;
}

namespace Graphics
{
    class RenderTarget;

    class CompositeRenderPass : public RenderPass
    {
    public:
        explicit CompositeRenderPass(Device& device, Resources::ShaderLibrary& shaderLibrary, Resources::SamplerLibrary& samplerLibrary, const std::shared_ptr<RenderTarget>& geometryRenderTarget);

        void Execute(Device& device, RenderQueue& renderQueue, RenderContext& renderContext) override;

    private:
        RenderObject _renderObject;
    };
}
