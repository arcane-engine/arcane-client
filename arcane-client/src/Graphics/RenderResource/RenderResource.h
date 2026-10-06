#pragma once

namespace Graphics
{
    class Device;
    class RenderContext;

    class RenderResource
    {
    public:
        virtual ~RenderResource() = default;

        virtual void Bind(Device& device, const RenderContext& renderContext) = 0;
    };
}
