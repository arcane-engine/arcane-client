#pragma once

#include <d3d11.h>

#include "Graphics/Device.h"
#include "Graphics/GraphicsException.h"
#include "Graphics/RenderResource/ConstantBuffer.h"

namespace Graphics
{

    template <typename T>
    ConstantBuffer<T>::ConstantBuffer(Device& device, const T& source, const UINT slot, const bool vertexShader, const bool pixelShader)
        : _vertexShader(vertexShader), _pixelShader(pixelShader), _slot(slot)
    {
        D3D11_BUFFER_DESC desc = {};
        desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        desc.Usage = D3D11_USAGE_DYNAMIC;
        desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        desc.ByteWidth = sizeof(source);

        D3D11_SUBRESOURCE_DATA data = {};
        data.pSysMem = &source;

        device.SetMarker();
        const auto hResult = device.GetDevice()->CreateBuffer(&desc, &data, &_buffer);
        if (FAILED(hResult))
        {
            throw GraphicsException("Unable to create constant buffer.", hResult, device);
        }
    }

    template <typename T>
    void ConstantBuffer<T>::Bind(const Device& device) const noexcept
    {
        if (_vertexShader)
        {
            device.GetDeviceContext()->VSSetConstantBuffers(_slot, 1u, _buffer.GetAddressOf());
        }
        if (_pixelShader)
        {
            device.GetDeviceContext()->PSSetConstantBuffers(_slot, 1u, _buffer.GetAddressOf());
        }
    }
}
