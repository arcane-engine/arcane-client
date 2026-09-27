#pragma once

namespace Graphics
{
    class Device;

    class RenderResource
    {
    public:
        virtual ~RenderResource() = default;

        virtual void Bind(const Device& device) const noexcept = 0;
    };
}
