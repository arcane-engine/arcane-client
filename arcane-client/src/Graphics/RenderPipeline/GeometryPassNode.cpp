#include "GeometryPassNode.h"

#include "Graphics/RenderQueue.h"

namespace Graphics
{
    void GeometryPassNode::Execute(Device& device, RenderQueue& renderQueue)
    {
        renderQueue.Execute(device);
    }
}
