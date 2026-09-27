#include "Graphics/RenderResource/Topology.h"

#include "Graphics/Device.h"

namespace Graphics
{
    Topology::Topology(const D3D11_PRIMITIVE_TOPOLOGY topology) noexcept
        : _topology(topology)
    {}

    void Topology::Bind(const Device& device) const noexcept
    {
        device.GetDeviceContext()->IASetPrimitiveTopology(_topology);
    }
}
