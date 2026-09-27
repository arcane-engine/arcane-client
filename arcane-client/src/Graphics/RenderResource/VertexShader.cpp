#include "Graphics/RenderResource/VertexShader.h"

#include "Graphics/Device.h"

namespace Graphics
{
    VertexShader::VertexShader(const Microsoft::WRL::ComPtr<ID3D11VertexShader>& shader) noexcept
        : _shader(shader)
    {}

    void VertexShader::Bind(const Device& device) const noexcept
    {
        device.GetDeviceContext()->VSSetShader(_shader.Get(), nullptr, 0);
    }
}
