#pragma once

#include <d3d11.h>
#include <wrl/client.h>

#include "RenderResource.h"

namespace Graphics
{
    class Texture final : public RenderResource
    {
    public:
        Texture(const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& shaderResourceView, int slot);

        void Bind(const Device& device) const noexcept override;

    private:
        int _slot;
        Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> _shaderResourceView;
    };
}
