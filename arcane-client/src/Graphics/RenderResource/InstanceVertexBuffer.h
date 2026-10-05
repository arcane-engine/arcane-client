#pragma once

#include <wrl/client.h>

#include "Graphics/RenderResource/RenderResource.h"

struct ID3D11Buffer;

namespace Graphics
{
    class InstanceVertexBuffer final : public RenderResource
    {
    public:
        explicit InstanceVertexBuffer(int slot);

        void Bind(Device& device, const RenderContext& renderContext) noexcept override;

    private:
        int _slot;
        size_t _capacity;
        Microsoft::WRL::ComPtr<ID3D11Buffer> _buffer;
    };
}
