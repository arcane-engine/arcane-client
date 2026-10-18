#pragma once

#include "Graphics/RenderObject.h"
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
    class DepthStencil;
    class RenderTarget;

    class CompositionRenderPass : public RenderPass
    {
    public:
        explicit CompositionRenderPass(Device& device, Resources::ShaderLibrary& shaderLibrary, const Resources::SamplerLibrary& samplerLibrary, const Resources::DepthStencilStateLibrary& depthStencilStateLibrary, Resources::InputLayoutLibrary& inputLayoutLibrary, const std::shared_ptr<RenderTarget>& geometryRenderTarget, const std::shared_ptr<DepthStencil>& depthStencil);

        void Execute(Device& device, Core::Context& context) override;

    private:
        RenderObject _renderObject;
    };
}
