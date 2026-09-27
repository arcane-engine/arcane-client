#pragma once

#include "Graphics/RenderResource/VertexBuffer.h"

#include "Graphics/Device.h"
#include "Graphics/GraphicsException.h"

namespace Graphics
{
    template <class T>
    VertexBuffer::VertexBuffer(Device& device, const std::vector<T>& source)
        : _stride(sizeof(T))
    {
        D3D11_BUFFER_DESC desc = {};
        desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.ByteWidth = static_cast<UINT>(_stride * std::size(source));

        D3D11_SUBRESOURCE_DATA data = {};
        data.pSysMem = source.data();

        device.SetMarker();
        const auto hResult = device.GetDevice()->CreateBuffer(&desc, &data, &_buffer);
        if (FAILED(hResult))
        {
            throw GraphicsException("Unable to create vertex buffer.", hResult, device);
        }
    }

    inline void VertexBuffer::Bind(const Device& device) const noexcept
    {
        constexpr UINT offset = 0;

        device.GetDeviceContext()->IASetVertexBuffers(0, 1, _buffer.GetAddressOf(), &_stride, &offset);
    }
}
