#include "Graphics/RenderQueue/RenderCommand.h"

namespace Graphics
{
    RenderCommand::RenderCommand(const RenderObject& renderObject)
        : _renderObject(renderObject)
    {}

    RenderCommand::RenderCommand(const RenderObject& renderObject, const DirectX::XMMATRIX& worldMatrix)
        : _renderObject(renderObject), _worldMatrix(worldMatrix)
    {}

    RenderCommand::RenderCommand(const RenderObject& renderObject, std::span<const DirectX::XMMATRIX> instanceMatrices)
        : _renderObject(renderObject), _instanceMatrices(instanceMatrices)
    {}

    const RenderObject& RenderCommand::GetRenderObject() const noexcept
    {
        return _renderObject;
    }

    std::optional<DirectX::XMMATRIX> RenderCommand::GetWorldMatrix() const noexcept
    {
        return _worldMatrix;
    }

    std::optional<std::span<const DirectX::XMMATRIX>> RenderCommand::GetInstanceMatrices() const noexcept
    {
        return _instanceMatrices;
    }
}
