#pragma once

namespace Graphics
{
    class Device;
    class RenderContext;

    class RenderResource
    {
    public:
        virtual ~RenderResource() = default;

        virtual void Bind(const Device& device, const RenderContext& renderContext) const noexcept = 0;
    };
}
