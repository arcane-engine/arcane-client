#include "Graphics/RenderResource/VertexShader.h"

#include "Graphics/Device.h"

namespace Graphics
{
    VertexShader::VertexShader(const Microsoft::WRL::ComPtr<ID3D11VertexShader>& vertexShader) noexcept
        : _vertexShader(vertexShader)
    {}

    void VertexShader::Bind(Device& device, const RenderContext& renderContext) noexcept
    {
        if (device.GetContextCache().VertexShader != _vertexShader.Get())
        {
            device.GetDeviceContext()->VSSetShader(_vertexShader.Get(), nullptr, 0);
            device.GetContextCache().VertexShader = _vertexShader.Get();
        }
    }
}
