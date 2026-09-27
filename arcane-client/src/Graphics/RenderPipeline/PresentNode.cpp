#include "Graphics/RenderPipeline/PresentNode.h"

#include <intsafe.h>

#include "Graphics/Device.h"
#include "Graphics/GraphicsException.h"

namespace Graphics
{
    void PresentNode::Execute(Device& device, RenderQueue& renderQueue)
    {
        device.SetMarker();
        const auto hResult = device.GetSwapChain()->Present(1, 0);
        if (FAILED(hResult))
        {
            if (hResult == DXGI_ERROR_DEVICE_REMOVED)
            {
                throw GraphicsException("Graphics device removed.", device.GetDevice()->GetDeviceRemovedReason());
            }
            throw GraphicsException("Graphics failure.", hResult);
        }
    }
}
