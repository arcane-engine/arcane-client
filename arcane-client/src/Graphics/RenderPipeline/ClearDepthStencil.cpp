#include "Graphics/RenderPipeline/ClearDepthStencil.h"

#include "Graphics/RenderTarget/DepthStencil.h"

namespace Graphics
{
    ClearDepthStencil::ClearDepthStencil(const std::shared_ptr<DepthStencil>& depthStencil) noexcept
        : _depthStencil(depthStencil)
    {}

    void ClearDepthStencil::Execute(Device& device, RenderQueue& renderQueue)
    {
        _depthStencil->Clear(device);
    }
}
