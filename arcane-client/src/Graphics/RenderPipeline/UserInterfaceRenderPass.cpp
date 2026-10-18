#include "UserInterfaceRenderPass.h"

#include "Core/Context/Context.h"
#include "Graphics/RenderObject.h"

namespace Graphics
{
    void UserInterfaceRenderPass::Execute(Device& device, Core::Context& context)
    {
        for (auto& command : context.UserInterfaceRenderQueue.GetCommands())
        {
            context.Object.WorldMatrix = *command.GetWorldMatrix();
            command.GetRenderObject().Bind(device, context);
            command.GetRenderObject().Draw(device);
        }
    }
}
