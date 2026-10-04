#include "Graphics/RenderPipeline/Present.h"

#include <dxgi1_2.h>
#include <intsafe.h>

#include "Graphics/Device.h"
#include "Graphics/GraphicsException.h"

namespace Graphics
{
    void Present::Execute(Device& device, [[maybe_unused]] RenderQueue& renderQueue, [[maybe_unused]] RenderContext& renderContext)
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
