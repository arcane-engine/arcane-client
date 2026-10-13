#pragma once

namespace Core
{
    struct Context;
}

namespace Graphics
{
    class Device;

    class RenderResource
    {
    public:
        virtual ~RenderResource() = default;

        virtual void Bind(Device& device, const Core::Context& context) = 0;
    };
}
