#pragma once

#include <memory>

#include "Graphics/RenderPipeline/RenderNode.h"

namespace Graphics
{
    class RenderBuffer;

    class ClearBufferNode final : public RenderNode
    {
    public:
        explicit ClearBufferNode(const std::shared_ptr<RenderBuffer>& buffer);

        void Execute(Device& device, RenderQueue& renderQueue) override;

    private:
        std::shared_ptr<RenderBuffer> _buffer;
    };
}
