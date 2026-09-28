#pragma once

#include "Graphics/RenderObject.h"
#include "Graphics/RenderPipeline/RenderPass.h"

namespace Resources
{
    class ShaderLibrary;
}

namespace Graphics
{
    class RenderTarget;

    class CompositeRenderPass : public RenderPass
    {
    public:
        explicit CompositeRenderPass(Device& device, Resources::ShaderLibrary& shaderLibrary, const std::shared_ptr<RenderTarget>& geometryRenderTarget);

        void Execute(Device& device, RenderQueue& renderQueue) override;

    private:
        RenderObject _renderObject;
    };
}
