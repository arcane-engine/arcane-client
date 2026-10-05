#include "Graphics/RenderObject.h"

#include "Graphics/Device.h"
#include "Graphics/RenderResource/RenderResource.h"

namespace Graphics
{
    void RenderObject::Add(const std::shared_ptr<RenderResource>& resource)
    {
        _resources.push_back(resource);
    }

    void RenderObject::Bind(Device& device, const RenderContext& renderContext) const noexcept
    {
        for (const auto& resource : _resources)
        {
            resource->Bind(device, renderContext);
        }
    }

    void RenderObject::Draw(const Device& device) const noexcept
    {
        device.GetDeviceContext()->DrawIndexed(_indexCount, 0, 0);
    }

    void RenderObject::Draw(const Device& device, const int instanceCount) const noexcept
    {
        device.GetDeviceContext()->DrawIndexedInstanced(_indexCount, instanceCount, 0, 0, 0);
    }

    void RenderObject::SetIndexCount(const UINT indexCount) noexcept
    {
        _indexCount = indexCount;
    }

    UINT RenderObject::GetIndexCount() const noexcept
    {
        return _indexCount;
    }
}
