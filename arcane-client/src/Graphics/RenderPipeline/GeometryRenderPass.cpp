#include "GeometryRenderPass.h"

#include "Graphics/RenderQueue.h"

namespace Graphics
{
    void GeometryRenderPass::Execute(Device& device, RenderQueue& renderQueue, RenderContext& renderContext)
    {
        renderQueue.Execute(device, renderContext);
    }
}
