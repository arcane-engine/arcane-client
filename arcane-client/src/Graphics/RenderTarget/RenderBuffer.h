#pragma once

namespace Graphics
{
    class Device;

    class RenderBuffer
    {
    public:
        RenderBuffer(Device& device, int width, int height) noexcept;
        
        virtual ~RenderBuffer() = default;

        RenderBuffer(const RenderBuffer&) = delete;
        RenderBuffer& operator=(const RenderBuffer&) = delete;
        RenderBuffer(RenderBuffer&&) = delete;
        RenderBuffer& operator=(RenderBuffer&&) = delete;

        [[nodiscard]] int GetWidth() const noexcept;
        [[nodiscard]] int GetHeight() const noexcept;

        virtual void Clear() = 0;

    protected:
        Device& _device;
        int _width;
        int _height;
    };
}
