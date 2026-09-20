#include "Core/Input/MouseRawEvent.h"

namespace Core::Input
{
    MouseRawEvent::MouseRawEvent(const int x, const int y) noexcept
        : _x(x), _y(y)
    {}

    int MouseRawEvent::GetX() const noexcept
    {
        return _x;
    }

    int MouseRawEvent::GetY() const noexcept
    {
        return _y;
    }
}
