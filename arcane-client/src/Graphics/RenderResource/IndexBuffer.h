#pragma once

#include <vector>
#include <wrl/client.h>

#include "Graphics/RenderResource/VertexBuffer.h"

namespace Graphics
{
    class Device;

    class IndexBuffer final : public RenderResource
    {
    public:
        IndexBuffer(Device& device, const std::vector<unsigned int>& source);

        void Bind(const Device& device, const RenderContext& renderContext) const noexcept override;

    private:
        UINT _count;
        Microsoft::WRL::ComPtr<ID3D11Buffer> _buffer;
    };
}
