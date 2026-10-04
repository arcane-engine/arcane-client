#include "Graphics/RenderQueue.h"

#include <DirectXMath.h>

#include "Graphics/RenderContext.h"
#include "Graphics/RenderObject.h"

namespace Graphics
{
    void RenderQueue::Clear() noexcept
    {
        _commands.clear();
    }

    void RenderQueue::Add(const RenderObject& object)
    {
        _commands.push_back(RenderCommand(object));
    }

    void RenderQueue::Add(const RenderObject& object, const DirectX::XMMATRIX& worldMatrix)
    {
        _commands.push_back(RenderCommand(object, worldMatrix));
    }

    void RenderQueue::Execute(Device& device, RenderContext& renderContext) const noexcept
    {
        for (auto& command : _commands)
        {
            if (const auto worldMatrix = command.GetWorldMatrix())
            {
                renderContext.WorldMatrix = *worldMatrix;
                renderContext.WorldViewProjectionMatrix = *worldMatrix * renderContext.ViewProjectionMatrix;
            }

            command.GetRenderObject().Bind(device, renderContext);
            command.GetRenderObject().Draw(device);
        }
    }
}
