#pragma once

#include <wrl/client.h>

#include "Graphics/RenderResource/RenderResource.h"

struct ID3D11Buffer;

namespace Graphics
{
    template<typename T>
    class ConstantBuffer final : public RenderResource
    {
    public:
        ConstantBuffer(const Device& device, UINT slot, bool vertexShader = true, bool pixelShader = false);

        void Bind(Device& device, const Core::Context& context) noexcept override;
        void Update(const Device& device, const T& data) const noexcept;

    private:
        Microsoft::WRL::ComPtr<ID3D11Buffer> _buffer;
        UINT _slot;
        bool _vertexShader;
        bool _pixelShader;
    };
}

#include "Graphics/RenderResource/ConstantBuffer.inl"
