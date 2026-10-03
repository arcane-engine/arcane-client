#include "Graphics/RenderPipeline/ClearRenderTarget.h"

#include "Graphics/RenderTarget/RenderTarget.h"

namespace Graphics
{
    ClearRenderTarget::ClearRenderTarget(const std::shared_ptr<RenderTarget>& renderTarget)
        : _renderTarget(renderTarget)
    {}

    void ClearRenderTarget::Execute(Device& device, [[maybe_unused]] RenderQueue& renderQueue, [[maybe_unused]] RenderContext& renderContext)
    {
        _renderTarget->Clear(device);
    }
}
