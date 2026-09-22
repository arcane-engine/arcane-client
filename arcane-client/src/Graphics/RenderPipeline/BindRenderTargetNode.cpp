#include "Graphics/RenderPipeline/BindRenderTargetNode.h"

#include "Graphics/Device.h"
#include "Graphics/RenderTarget/DepthStencil.h"
#include "Graphics/RenderTarget/RenderTarget.h"

namespace Graphics
{
    BindRenderTargetNode::BindRenderTargetNode(const std::shared_ptr<RenderTarget>& renderTarget, const std::shared_ptr<DepthStencil>& depthStencil)
        : _renderTarget(renderTarget), _depthStencil(depthStencil)
    {}

    void BindRenderTargetNode::Execute(Device& device)
    {
        auto* const renderTargetView = _renderTarget ? _renderTarget->GetRenderTargetView() : nullptr;
        auto* const depthStencilView = _depthStencil ? _depthStencil->GetDepthStencilView() : nullptr;

        device.GetDeviceContext()->OMSetRenderTargets(1, &renderTargetView, depthStencilView);
    }
}
