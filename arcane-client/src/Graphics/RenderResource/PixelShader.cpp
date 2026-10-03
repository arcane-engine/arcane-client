#include "Graphics/RenderResource/PixelShader.h"

#include "Graphics/Device.h"

namespace Graphics
{
    PixelShader::PixelShader(const Microsoft::WRL::ComPtr<ID3D11PixelShader>& pixelShader) noexcept
        : _pixelShader(pixelShader)
    {}

    void PixelShader::Bind(Device& device, [[maybe_unused]] const RenderContext& renderContext) noexcept
    {
        auto& active = device.GetContextCache().PixelShader;
        auto* target = _pixelShader.Get();

        if (target != active)
        {
            device.GetDeviceContext()->PSSetShader(target, nullptr, 0);
            active = target;
        }
    }
}
