#pragma once

#include <DirectXMath.h>
#include <optional>
#include <span>

namespace Graphics
{
    class RenderObject;

    class RenderCommand
    {
    public:
        explicit RenderCommand(const RenderObject& renderObject);
        RenderCommand(const RenderObject& renderObject, const DirectX::XMMATRIX& worldMatrix);
        RenderCommand(const RenderObject& renderObject, std::span<const DirectX::XMMATRIX> instanceMatrices);

        [[nodiscard]] const RenderObject& GetRenderObject() const noexcept;
        [[nodiscard]] std::optional<DirectX::XMMATRIX> GetWorldMatrix() const noexcept;
        [[nodiscard]] std::optional<std::span<const DirectX::XMMATRIX>> GetInstanceMatrices() const noexcept;

    private:
        const RenderObject& _renderObject;
        std::optional<DirectX::XMMATRIX> _worldMatrix;
        std::optional<std::span<const DirectX::XMMATRIX>> _instanceMatrices;
    };
}
