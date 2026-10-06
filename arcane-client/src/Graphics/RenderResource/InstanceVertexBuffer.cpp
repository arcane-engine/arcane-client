#include "Graphics/RenderResource/InstanceVertexBuffer.h"

#include <algorithm>
#include <d3d11.h>
#include <DirectXMath.h>

#include "Graphics/Device.h"
#include "Graphics/GraphicsException.h"
#include "Graphics/RenderContext.h"
#include "Math/Math.h"

namespace Graphics
{
    InstanceVertexBuffer::InstanceVertexBuffer(const int slot)
        : _slot(slot), _capacity(0)
    {
    }

    void InstanceVertexBuffer::Bind(Device& device, const RenderContext& renderContext)
    {
        const auto matrices = renderContext.InstanceMatrices;
        if (matrices.empty())
            return;

        const auto requiredCount = matrices.size();

        if (!_buffer || requiredCount > _capacity)
        {
            _capacity = Math::Max(requiredCount, _capacity == 0 ? 256 : _capacity * 2);

            D3D11_BUFFER_DESC desc;
            desc.Usage = D3D11_USAGE_DYNAMIC;
            desc.ByteWidth = static_cast<UINT>(_capacity * sizeof(DirectX::XMMATRIX));
            desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
            desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
            desc.MiscFlags = 0;
            desc.StructureByteStride = 0;

            device.SetMarker();
            const auto hResult = device.GetDevice()->CreateBuffer(&desc, nullptr, _buffer.ReleaseAndGetAddressOf());
            if (FAILED(hResult))
            {
                throw GraphicsException("Failed to create instance vertex buffer.", hResult, device.GetDebugMessages());
            }
        }

        D3D11_MAPPED_SUBRESOURCE mappedResource = {};
        if (SUCCEEDED(device.GetDeviceContext()->Map(_buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource)))
        {
            std::memcpy(mappedResource.pData, matrices.data(), matrices.size_bytes());
            device.GetDeviceContext()->Unmap(_buffer.Get(), 0);
        }

        constexpr UINT stride = sizeof(DirectX::XMMATRIX);
        constexpr UINT offset = 0;
        device.GetDeviceContext()->IASetVertexBuffers(_slot, 1, _buffer.GetAddressOf(), &stride, &offset);
    }
}
