#pragma once

#include <memory>

#include "Graphics/RenderPipeline/RenderPass.h"

namespace Graphics
{
    class DepthStencil;

    class ClearDepthStencil final : public RenderPass
    {
    public:
        explicit ClearDepthStencil(const std::shared_ptr<DepthStencil>& depthStencil) noexcept;

        void Execute(Device& device, RenderQueue& renderQueue) override;

    private:
        std::shared_ptr<DepthStencil> _depthStencil;
    };
}
