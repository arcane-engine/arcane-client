#pragma once

#include <intsafe.h>
#include <memory>
#include <vector>

namespace Graphics
{
    class RenderResource;
    class Device;

    class RenderObject
    {
    public:
        RenderObject() = default;

        void Add(const std::shared_ptr<RenderResource>& resource);

        void Bind(const Device& device) const noexcept;

        void Draw(const Device& device) const noexcept;

        void SetIndexCount(UINT indexCount) noexcept;
        [[nodiscard]] UINT GetIndexCount() const noexcept;

    private:
        std::vector<std::shared_ptr<RenderResource>> _resources;
        UINT _indexCount = 0;
    };
}
