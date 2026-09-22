#include "Graphics/RenderPipeline/BindRenderTargetNode.h"

#include "Graphics/Device.h"
#include "Graphics/RenderTarget/RenderTarget.h"

namespace Graphics
{
    BindRenderTargetNode::BindRenderTargetNode(const std::shared_ptr<RenderTarget>& renderTarget)
        : _renderTarget(renderTarget)
    {
    }

    void BindRenderTargetNode::Execute(Device& device)
    {
        device.GetDeviceContext()->OMSetRenderTargets(1, _renderTarget->GetRenderTargetView().GetAddressOf(), nullptr);
    }
}
