#pragma once

#include <DirectXMath.h>

namespace Graphics
{
    class RenderObject;

    class RenderCommand
    {
    public:
        RenderCommand(const RenderObject& renderObject, const DirectX::XMMATRIX& transform);

        [[nodiscard]] const RenderObject& GetRenderObject() const noexcept;
        [[nodiscard]] DirectX::XMMATRIX GetTransform() const noexcept;

    private:
        const RenderObject& _renderObject;
        DirectX::XMMATRIX _transform;
    };
}
