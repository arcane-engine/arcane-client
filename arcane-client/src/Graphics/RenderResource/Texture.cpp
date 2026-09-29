#include "Texture.h"

#include "Graphics/Device.h"

namespace Graphics
{
    Texture::Texture(const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& shaderResourceView, const int slot)
        : _slot(slot), _shaderResourceView(shaderResourceView)
    {}

    void Texture::Bind(const Device& device, const RenderContext& renderContext) const noexcept
    {
        ID3D11ShaderResourceView* srv = _shaderResourceView.Get();
        device.GetDeviceContext()->PSSetShaderResources(_slot, 1, &srv);
    }
}
