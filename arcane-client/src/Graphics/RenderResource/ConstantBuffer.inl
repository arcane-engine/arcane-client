#pragma once

#include <d3d11.h>

#include "Data/CameraTransformBuffer.h"
#include "Data/ObjectTransformBuffer.h"
#include "Graphics/Device.h"
#include "Graphics/GraphicsException.h"
#include "Graphics/RenderResource/ConstantBuffer.h"

namespace Graphics
{
    template <typename T>
    ConstantBuffer<T>::ConstantBuffer(const Device& device, const UINT slot, const bool vertexShader, const bool pixelShader)
        : _vertexShader(vertexShader), _pixelShader(pixelShader), _slot(slot)
    {
        D3D11_BUFFER_DESC desc = {};
        desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        desc.Usage = D3D11_USAGE_DYNAMIC;
        desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        desc.ByteWidth = static_cast<UINT>(sizeof(T));

        device.SetMarker();
        const auto hResult = device.GetDevice()->CreateBuffer(&desc, nullptr, &_buffer);
        if (FAILED(hResult))
        {
            throw GraphicsException("Unable to create empty constant buffer.", hResult, device.GetDebugMessages());
        }
    }

    template <typename T>
    void ConstantBuffer<T>::Bind(Device& device, const RenderContext& renderContext) noexcept
    {

        if constexpr (std::is_same_v<T, CameraTransformBuffer>)
        {
            Update(device, CameraTransformBuffer::FromRenderContext(renderContext));
        }
        if constexpr (std::is_same_v<T, ObjectTransformBuffer>)
        {
            Update(device, ObjectTransformBuffer::FromRenderContext(renderContext));
        }

        auto* target = _buffer.Get();

        if (_vertexShader)
        {
            auto& active = device.GetContextCache().VertexShaderConstantBuffers[_slot];
            if (target != active)
            {
                device.GetDeviceContext()->VSSetConstantBuffers(_slot, 1u, _buffer.GetAddressOf());
                active = target;
            }
        }
        if (_pixelShader)
        {
            auto& active = device.GetContextCache().PixelShaderConstantBuffers[_slot];
            if (target != active)
            {
                device.GetDeviceContext()->PSSetConstantBuffers(_slot, 1u, _buffer.GetAddressOf());
                active = target;
            }
        }
    }

    template <typename T>
    void ConstantBuffer<T>::Update(const Device& device, const T& data) const noexcept
    {
        D3D11_MAPPED_SUBRESOURCE resource{};
        const auto hResult = device.GetDeviceContext()->Map(_buffer.Get(), 0u, D3D11_MAP_WRITE_DISCARD, 0u, &resource);
        if (SUCCEEDED(hResult))
        {
            std::memcpy(resource.pData, &data, sizeof(T));
            device.GetDeviceContext()->Unmap(_buffer.Get(), 0u);
        }
    }
}
