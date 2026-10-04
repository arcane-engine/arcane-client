#pragma once

#include <d3d11.h>
#include <wrl/client.h>

#include "Graphics/RenderResource/RenderResource.h"

namespace Graphics
{
    template<typename T>
    class ConstantBuffer final : public RenderResource
    {
    public:
        ConstantBuffer(const Device& device, UINT slot, bool vertexShader = true, bool pixelShader = false);

        void Bind(Device& device, const RenderContext& renderContext) noexcept override;
        void Update(const Device& device, const T& data) const noexcept;

    private:
        bool _vertexShader;
        bool _pixelShader;
        UINT _slot;
        Microsoft::WRL::ComPtr<ID3D11Buffer> _buffer;
    };
}

#include "Graphics/RenderResource/ConstantBuffer.inl"
