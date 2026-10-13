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

    void RenderQueue::Execute(Device& device, Core::Context& context) const noexcept
    {
        for (auto& command : _commands)
        {
            if (const auto worldMatrixInstances = command.GetWorldMatrixInstances())
            {
                context.Object.WorldMatrixInstances = *worldMatrixInstances;
                command.GetRenderObject().Bind(device, context);
                command.GetRenderObject().Draw(device, static_cast<int>(worldMatrixInstances->size()));
            }
            else if (const auto worldMatrix = command.GetWorldMatrix())
            {
                context.Object.WorldMatrix = *worldMatrix;
                context.Object.WorldViewProjectionMatrix = *worldMatrix * context.Camera.ViewProjectionMatrix;
                command.GetRenderObject().Bind(device, context);
                command.GetRenderObject().Draw(device);
            }
            else
            {
                command.GetRenderObject().Bind(device, context);
            }
        }
    }
}
