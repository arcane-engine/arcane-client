#include "Graphics/RenderPipeline/BindRenderTarget.h"

#include "Graphics/Device.h"
#include "Graphics/RenderTarget/DepthStencil.h"
#include "Graphics/RenderTarget/RenderTarget.h"

namespace Graphics
{
    BindRenderTarget::BindRenderTarget(const std::shared_ptr<RenderTarget>& renderTarget, const std::shared_ptr<DepthStencil>& depthStencil)
        : _renderTarget(renderTarget), _depthStencil(depthStencil)
    {}

    void BindRenderTarget::Execute(Device& device, [[maybe_unused]] RenderQueue& renderQueue, [[maybe_unused]] RenderContext& renderContext)
    {
        auto* const renderTargetView = _renderTarget ? _renderTarget->GetRenderTargetView() : nullptr;
        auto* const depthStencilView = _depthStencil ? _depthStencil->GetDepthStencilView() : nullptr;

        device.GetDeviceContext()->OMSetRenderTargets(1, &renderTargetView, depthStencilView);
    }
}
