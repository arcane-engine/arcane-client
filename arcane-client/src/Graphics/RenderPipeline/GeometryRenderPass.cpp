#include "GeometryRenderPass.h"

#include "Core/Context/Context.h"
#include "Graphics/RenderObject.h"
#include "Graphics/RenderQueue.h"

namespace Graphics
{
    void GeometryRenderPass::Execute(Device& device, Core::Context& context)
    {
        for (auto& command : context.GeometryRenderQueue.GetCommands())
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
