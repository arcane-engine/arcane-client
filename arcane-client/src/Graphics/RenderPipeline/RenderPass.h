#pragma once

namespace Graphics
{
    class RenderQueue;
    class Device;

    class RenderPass
    {
    public:
        RenderPass() = default;

        virtual ~RenderPass() = default;

        RenderPass(const RenderPass&) = delete;
        RenderPass& operator=(const RenderPass&) = delete;
        RenderPass(RenderPass&&) noexcept = default;
        RenderPass& operator=(RenderPass&&) noexcept = default;

        virtual void Execute(Device& device, RenderQueue& renderQueue) = 0;
    };
}
