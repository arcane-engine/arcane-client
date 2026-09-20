#pragma once

#include <cstdint>

namespace Core::Input
{
    class MouseEvent
    {
    public:
        enum class Type : std::uint8_t
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

        MouseEvent(Type type, int x, int y, bool left, bool right) noexcept;

        [[nodiscard]] Type GetType() const noexcept;
        [[nodiscard]] int GetX() const noexcept;
        [[nodiscard]] int GetY() const noexcept;
        [[nodiscard]] bool IsLeftPressed() const noexcept;
        [[nodiscard]] bool IsRightPressed() const noexcept;

    private:
        Type _type;
        int _x;
        int _y;
        bool _left;
        bool _right;
    };
}
