#include "Graphics/RenderResource/Texture.h"

#include "Graphics/Device.h"

namespace Graphics
{
    Texture::Texture(const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& shaderResourceView, const int slot, const bool vertexShader, const bool pixelShader)
        : _shaderResourceView(shaderResourceView), _slot(slot), _vertexShader(vertexShader), _pixelShader(pixelShader)
    {}

    void Texture::Bind(Device& device, [[maybe_unused]] const Core::Context& context) noexcept
    {
        auto* target = _shaderResourceView.Get();

        if (_vertexShader)
        {
            auto& active = device.GetContextCache().VertexShaderTextures[_slot];

            if (target != active)
            {
                device.GetDeviceContext()->VSSetShaderResources(_slot, 1, &target);
                active = target;
            }
        }
        if (_pixelShader)
        {
            auto& active = device.GetContextCache().PixelShaderTextures[_slot];

            if (target != active)
            {
                device.GetDeviceContext()->PSSetShaderResources(_slot, 1, &target);
                active = target;
            }
        }
    }
}
