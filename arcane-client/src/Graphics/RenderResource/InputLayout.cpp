#include "Graphics/RenderResource/InputLayout.h"

#include "Graphics/Device.h"
#include "Graphics/GraphicsException.h"

namespace Graphics
{
    InputLayout::InputLayout(const Device& device, const std::vector<D3D11_INPUT_ELEMENT_DESC>& inputLayout, ID3DBlob* blob)
    {
        device.SetMarker();
        const auto hResult = device.GetDevice()->CreateInputLayout(inputLayout.data(), static_cast<UINT>(inputLayout.size()), blob->GetBufferPointer(), blob->GetBufferSize(), &_inputLayout);
        if (FAILED(hResult))
        {
            throw GraphicsException("Unable to create input layout.", hResult, device);
        }
    }

    void InputLayout::Bind(Device& device, [[maybe_unused]] const RenderContext& renderContext) noexcept
    {
        auto& active = device.GetContextCache().InputLayout;
        auto* target = _inputLayout.Get();

        if (target != active)
        {
            device.GetDeviceContext()->IASetInputLayout(target);
            active = target;
        }
    }
}
