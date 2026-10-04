#pragma once

#include <wrl/client.h>

#include "Graphics/RenderResource/RenderResource.h"

struct ID3D11VertexShader;

namespace Graphics
{
    class VertexShader final : public RenderResource
    {
    public:
        explicit VertexShader(const Microsoft::WRL::ComPtr<ID3D11VertexShader>& vertexShader) noexcept;

        void Bind(Device& device, const RenderContext& renderContext) noexcept override;

    private:
        Microsoft::WRL::ComPtr<ID3D11VertexShader> _vertexShader;
    };
}
