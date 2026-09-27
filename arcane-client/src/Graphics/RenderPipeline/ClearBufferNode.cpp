#include "Graphics/RenderPipeline/ClearBufferNode.h"

#include "Graphics/RenderTarget/RenderBuffer.h"

namespace Graphics
{
    ClearBufferNode::ClearBufferNode(const std::shared_ptr<RenderBuffer>& buffer)
        : _buffer(buffer)
    {}

    void ClearBufferNode::Execute(Device& device, RenderQueue& renderQueue)
    {
        _buffer->Clear();
    }
}
