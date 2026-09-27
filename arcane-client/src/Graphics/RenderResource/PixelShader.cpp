#include "Graphics/RenderResource/PixelShader.h"

#include "Graphics/Device.h"

namespace Graphics
{
    PixelShader::PixelShader(const Microsoft::WRL::ComPtr<ID3D11PixelShader>& shader) noexcept
        : _shader(shader)
    {}

    void PixelShader::Bind(const Device& device) const noexcept
    {
        device.GetDeviceContext()->PSSetShader(_shader.Get(), nullptr, 0);
    }
}
