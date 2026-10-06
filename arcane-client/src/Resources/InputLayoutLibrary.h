#pragma once

#include <span>

#include "DepthStencilStateLibrary.h"

namespace Graphics
{
    class Device;
}

namespace Resources
{
    class ShaderLibrary;

    enum class InputLayoutType : std::uint8_t
    {
        PositionTexture,
        PositionNormalTexture,
        PositionNormalTextureInstanced
    };

    class InputLayoutLibrary
    {
    public:
        explicit InputLayoutLibrary(const Graphics::Device& device, ShaderLibrary& shaderLibrary);

        [[nodiscard]] const Microsoft::WRL::ComPtr<ID3D11InputLayout>& GetInputLayout(InputLayoutType type);

    private:
        void CreateInputLayout(const Graphics::Device& device, InputLayoutType type, std::span<const D3D11_INPUT_ELEMENT_DESC> inputLayout, ID3DBlob* vertexShaderBlob);

        std::array<Microsoft::WRL::ComPtr<ID3D11InputLayout>, 3> _inputLayouts;
    };
}
