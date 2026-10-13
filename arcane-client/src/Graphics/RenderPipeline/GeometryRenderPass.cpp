#include "GeometryRenderPass.h"

#include "Graphics/RenderQueue.h"

namespace Graphics
{
    void GeometryRenderPass::Execute(Device& device, RenderQueue& renderQueue, Core::Context& context)
    {
        renderQueue.Execute(device, context);
    }
}
