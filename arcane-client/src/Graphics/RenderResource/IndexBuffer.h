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
        IndexBuffer(Device& device, const std::vector<unsigned int>& indexBuffer);

        void Bind(Device& device, const RenderContext& renderContext) noexcept override;

    private:
        UINT _count;
        Microsoft::WRL::ComPtr<ID3D11Buffer> _indexBuffer;
    };
}
