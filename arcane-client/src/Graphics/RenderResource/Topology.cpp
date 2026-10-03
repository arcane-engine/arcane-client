#include "Graphics/RenderResource/Topology.h"

#include "Graphics/Device.h"

namespace Graphics
{
    Topology::Topology(const D3D11_PRIMITIVE_TOPOLOGY topology) noexcept
        : _topology(topology)
    {}

    void Topology::Bind(Device& device, [[maybe_unused]] const RenderContext& renderContext) noexcept
    {
        auto& active = device.GetContextCache().Topology;
        const auto target = _topology;

        if (target != active)
        {
            device.GetDeviceContext()->IASetPrimitiveTopology(target);
            active = target;
        }
    }
}
