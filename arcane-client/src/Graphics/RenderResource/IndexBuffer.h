#pragma once

#include <span>
#include <wrl/client.h>

#include "Graphics/RenderResource/RenderResource.h"

struct ID3D11Buffer;

namespace Graphics
{
    class IndexBuffer final : public RenderResource
    {
    public:
        IndexBuffer(const Device& device, const std::span<const unsigned int>& indexBuffer);

        void Bind(Device& device, const RenderContext& renderContext) noexcept override;

    private:
        UINT _count;
        Microsoft::WRL::ComPtr<ID3D11Buffer> _indexBuffer;
    };
}
