#pragma once

#include <wrl/client.h>

#include "Graphics/RenderResource/RenderResource.h"

struct ID3D11ShaderResourceView;

namespace Graphics
{
    class Texture final : public RenderResource
    {
    public:
        Texture(const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& shaderResourceView, int slot);

        void Bind(Device& device, const RenderContext& renderContext) noexcept override;

    private:
        Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> _shaderResourceView;
        int _slot;
    };
}
