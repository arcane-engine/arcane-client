#include "Graphics/RenderResource/VertexShader.h"

#include "Graphics/Device.h"

namespace Graphics
{
    VertexShader::VertexShader(const Microsoft::WRL::ComPtr<ID3D11VertexShader>& vertexShader) noexcept
        : _vertexShader(vertexShader)
    {}

    void VertexShader::Bind(Device& device, [[maybe_unused]] const RenderContext& renderContext) noexcept
    {
        auto& active = device.GetContextCache().VertexShader;
        auto* target = _vertexShader.Get();

        if (target != active)
        {
            device.GetDeviceContext()->VSSetShader(target, nullptr, 0);
            active = target;
        }
    }
}
