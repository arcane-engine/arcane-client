#pragma once

namespace Graphics
{
    class Device;
}

namespace Graphics
{
    class RenderNode
    {
    public:
        RenderNode() = default;

        virtual ~RenderNode() = default;

        RenderNode(const RenderNode&) = delete;
        RenderNode& operator=(const RenderNode&) = delete;
        RenderNode(RenderNode&&) noexcept = default;
        RenderNode& operator=(RenderNode&&) noexcept = default;

        virtual void Execute(Device& device) = 0;
    };
}
