#pragma once

#include <cstdint>

namespace Core::Input
{
    enum class MouseEventType : std::uint8_t
    {
        LeftDown,
        LeftUp,
        RightDown,
        RightUp,
        WheelUp,
        WheelDown,
        Move,
        Enter,
        Leave
    };

    struct MouseEvent
    {
        MouseEventType Type;
        int X;
        int Y;
        bool LeftPressed;
        bool RightPressed;

        MouseEvent(MouseEventType type, int x, int y, bool leftPressed, bool rightPressed) noexcept;
    };
}
