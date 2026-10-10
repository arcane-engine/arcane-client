#pragma once

#include <vector>
#include <wrl/client.h>

#include "Graphics/RenderResource/RenderResource.h"

struct ID3D11Buffer;

namespace Graphics
{
    class VertexBuffer final : public RenderResource
    {
    public:
        template<class T>
        VertexBuffer(Device& device, const std::vector<T>& vertexBuffer);
        VertexBuffer(const Device& device, const std::vector<std::byte>& vertexBuffer, std::size_t stride);

        void Bind(Device& device, const RenderContext& renderContext) noexcept override;

    private:
        Microsoft::WRL::ComPtr<ID3D11Buffer> _vertexBuffer;
        UINT _stride;
    };
}

#include "Graphics/RenderResource/VertexBuffer.inl"