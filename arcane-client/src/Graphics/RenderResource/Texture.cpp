#include "Texture.h"

#include "Graphics/Device.h"

namespace Graphics
{
    Texture::Texture(const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& shaderResourceView, const int slot)
        : _slot(slot), _shaderResourceView(shaderResourceView)
    {}

    void Texture::Bind(Device& device, [[maybe_unused]] const RenderContext& renderContext) noexcept
    {
        auto& active = device.GetContextCache().Textures[_slot];
        auto* target = _shaderResourceView.Get();

        if (target != active)
        {
            device.GetDeviceContext()->PSSetShaderResources(_slot, 1, &target);
            active = target;
        }
    }
}
