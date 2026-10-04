#pragma once

#include "Graphics/RenderResource/VertexBuffer.h"

#include "Graphics/Device.h"
#include "Graphics/GraphicsException.h"

namespace Graphics
{
    template <class T>
    VertexBuffer::VertexBuffer(Device& device, const std::vector<T>& vertexBuffer)
        : _stride(sizeof(T))
    {
        D3D11_BUFFER_DESC desc = {};
        desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.ByteWidth = static_cast<UINT>(_stride * std::size(vertexBuffer));

        D3D11_SUBRESOURCE_DATA data = {};
        data.pSysMem = vertexBuffer.data();

        device.SetMarker();
        const auto hResult = device.GetDevice()->CreateBuffer(&desc, &data, &_vertexBuffer);
        if (FAILED(hResult))
        {
            throw GraphicsException("Unable to create vertex buffer.", hResult, device.GetDebugMessages());
        }
    }

    inline void VertexBuffer::Bind(Device& device, [[maybe_unused]] const RenderContext& renderContext) noexcept
    {
        auto& active = device.GetContextCache().VertexBuffer;
        auto* target = _vertexBuffer.Get();

        if (target != active)
        {
            constexpr UINT offset = 0;
            device.GetDeviceContext()->IASetVertexBuffers(0, 1, &target, &_stride, &offset);
            active = target;
        }
    }
}
