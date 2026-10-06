#include "Graphics/RenderResource/InputLayout.h"

#include "Graphics/Device.h"

namespace Graphics
{
    InputLayout::InputLayout(const Microsoft::WRL::ComPtr<ID3D11InputLayout>& inputLayout)
        : _inputLayout(inputLayout)
    {}

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
