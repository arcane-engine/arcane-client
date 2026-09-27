#include "IndexBuffer.h"

#include "Graphics/Device.h"
#include "Graphics/GraphicsException.h"

namespace Graphics
{
    IndexBuffer::IndexBuffer(Device& device, const std::vector<unsigned int>& source)
        : _count(static_cast<UINT>(source.size()))
    {
        D3D11_BUFFER_DESC desc = {};
        desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.ByteWidth = static_cast<UINT>(sizeof(unsigned int) * _count);

        D3D11_SUBRESOURCE_DATA data = {};
        data.pSysMem = source.data();

        device.SetMarker();
        const auto hResult = device.GetDevice()->CreateBuffer(&desc, &data, &_buffer);
        if (FAILED(hResult))
        {
            throw GraphicsException("Unable to crete index buffer.", hResult, device);
        }
    }

    void IndexBuffer::Bind(const Device& device) const noexcept
    {
        device.GetDeviceContext()->IASetIndexBuffer(_buffer.Get(), DXGI_FORMAT_R32_UINT, 0);
    }
}
