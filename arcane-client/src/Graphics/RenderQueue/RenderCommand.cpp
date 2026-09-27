#include "RenderCommand.h"

namespace Graphics
{
    RenderCommand::RenderCommand(const RenderObject& renderObject, const DirectX::XMMATRIX& transform)
        : _renderObject(renderObject), _transform(transform)
    {
    }

    const RenderObject& RenderCommand::GetRenderObject() const noexcept
    {
        return _renderObject;
    }

    DirectX::XMMATRIX RenderCommand::GetTransform() const noexcept
    {
        return _transform;
    }
}
