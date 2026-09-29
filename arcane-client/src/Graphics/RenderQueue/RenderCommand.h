#pragma once

#include <DirectXMath.h>
#include <optional>

namespace Graphics
{
    class RenderObject;

    class RenderCommand
    {
    public:
        explicit RenderCommand(const RenderObject& renderObject);
        RenderCommand(const RenderObject& renderObject, const DirectX::XMMATRIX& worldMatrix);

        [[nodiscard]] const RenderObject& GetRenderObject() const noexcept;
        [[nodiscard]] std::optional<DirectX::XMMATRIX> GetWorldMatrix() const noexcept;

    private:
        const RenderObject& _renderObject;
        std::optional<DirectX::XMMATRIX> _worldMatrix;
    };
}
