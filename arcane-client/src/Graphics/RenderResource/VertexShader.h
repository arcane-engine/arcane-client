#pragma once

#include <d3d11.h>
#include <wrl/client.h>

#include "Graphics/RenderResource/RenderResource.h"

namespace Graphics
{
    class Device;

    class VertexShader final : public RenderResource
    {
    public:
        explicit VertexShader(const Microsoft::WRL::ComPtr<ID3D11VertexShader>& vertexShader) noexcept;

        void Bind(Device& device, const RenderContext& renderContext) noexcept override;

    private:
        Microsoft::WRL::ComPtr<ID3D11VertexShader> _vertexShader;
    };
}
