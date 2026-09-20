#include "Graphics/Buffer/RenderBuffer.h"

namespace Graphics::Buffer
{
    RenderBuffer::RenderBuffer(Device& device, const int width, const int height) noexcept
        : _device(device), _width(width), _height(height)
    {}

    int RenderBuffer::GetWidth() const noexcept
    {
        return _width;
    }

    int RenderBuffer::GetHeight() const noexcept
    {
        return _height;
    }
}
    