#include "Graphics/RenderResource/InputLayout.h"

#include "Graphics/Device.h"
#include "Graphics/GraphicsException.h"

namespace Graphics
{
    InputLayout::InputLayout(Device& device, const std::vector<D3D11_INPUT_ELEMENT_DESC>& input, const Microsoft::WRL::ComPtr<ID3DBlob>& blob)
    {
        device.SetMarker();
        const auto hResult = device.GetDevice()->CreateInputLayout(input.data(), static_cast<UINT>(input.size()), blob->GetBufferPointer(), blob->GetBufferSize(), &_layout);
        if (FAILED(hResult))
        {
            throw GraphicsException("Unable to create input layout.", hResult, device);
        }
    }

    void InputLayout::Bind(const Device& device, const RenderContext& renderContext) const noexcept
    {
        device.GetDeviceContext()->IASetInputLayout(_layout.Get());
    }
}
