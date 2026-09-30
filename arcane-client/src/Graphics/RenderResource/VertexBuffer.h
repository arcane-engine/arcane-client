#pragma once

#include <d3d11.h>
#include <vector>
#include <wrl/client.h>

#include "Graphics/RenderResource/RenderResource.h"

namespace Graphics
{
    class VertexBuffer final : public RenderResource
    {
    public:
        template<class T>
        VertexBuffer(Device& device, const std::vector<T>& vertexBuffer);

        void Bind(Device& device, const RenderContext& renderContext) noexcept override;

    private:
        UINT _stride;
        Microsoft::WRL::ComPtr<ID3D11Buffer> _vertexBuffer;
    };
}

#include "Graphics/RenderResource/VertexBuffer.inl"