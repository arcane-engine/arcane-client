#pragma once

#include <d3d11.h>
#include <wrl/client.h>

#include "Graphics/RenderResource/RenderResource.h"

namespace Graphics
{
    class InputLayout final : public RenderResource
    {
    public:
        explicit InputLayout(const Microsoft::WRL::ComPtr<ID3D11InputLayout>& inputLayout);

        void Bind(Device& device, const RenderContext& renderContext) noexcept override;

    private:
        Microsoft::WRL::ComPtr<ID3D11InputLayout> _inputLayout;
    };
}
