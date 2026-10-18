#include "Graphics/RenderQueue.h"

#include <DirectXMath.h>

#include "Core/Context/Context.h"
#include "Graphics/RenderObject.h"

namespace Graphics
{
    void RenderQueue::Clear() noexcept
    {
        _commands.clear();
    }

    const std::vector<RenderCommand>& RenderQueue::GetCommands() noexcept
    {
        return _commands;
    }

    void RenderQueue::Add(const RenderObject& object) noexcept
    {
        _commands.push_back(RenderCommand(object));
    }

    void RenderQueue::Add(const RenderObject& object, const DirectX::XMMATRIX& worldMatrix) noexcept
    {
        _commands.push_back(RenderCommand(object, worldMatrix));
    }

    void RenderQueue::Add(const RenderObject& object, const std::span<const DirectX::XMMATRIX> worldMatrixInstances) noexcept
    {
        _commands.push_back(RenderCommand(object, worldMatrixInstances));
    }
}
