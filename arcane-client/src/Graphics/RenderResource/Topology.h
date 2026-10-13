#pragma once

#include <d3d11.h>

#include "Graphics/RenderResource/RenderResource.h"

namespace Graphics
{
    class Topology final : public RenderResource
    {
    public:
        explicit Topology(D3D11_PRIMITIVE_TOPOLOGY topology) noexcept;

        void Bind(Device& device, const Core::Context& context) noexcept override;

    private:
        D3D11_PRIMITIVE_TOPOLOGY _topology;
    };
}
