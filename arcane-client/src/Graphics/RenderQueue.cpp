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

    void RenderQueue::Add(const RenderObject& object, const std::span<const DirectX::XMMATRIX> instanceMatrices) noexcept
    {
        _commands.push_back(RenderCommand(object, instanceMatrices));
    }

    void RenderQueue::Execute(Device& device, Core::Context& context) const noexcept
    {
        for (auto& command : _commands)
        {
            auto instanceCount = 0;

            if (const auto instanceMatrices = command.GetInstanceMatrices())
            {
                context.InstanceMatrices = *instanceMatrices;
                instanceCount = static_cast<int>(instanceMatrices->size());
            }
            if (const auto worldMatrix = command.GetWorldMatrix())
            {
                context.Object = {
                    .WorldMatrix = *worldMatrix,
                    .WorldViewProjectionMatrix = *worldMatrix * context.Camera.ViewProjectionMatrix
                };
            }

            command.GetRenderObject().Bind(device, context);
            if (instanceCount == 0)
            {
                command.GetRenderObject().Draw(device);
            }
            else
            {
                command.GetRenderObject().Draw(device, instanceCount);
            }
        }
    }
}
