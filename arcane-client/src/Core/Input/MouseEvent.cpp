#include "Core/Input/MouseEvent.h"

namespace Core::Input
{
    MouseEvent::MouseEvent(const MouseEventType type, const int x, const int y, const bool leftPressed, const bool rightPressed) noexcept
        : Type(type), X(x), Y(y), LeftPressed(leftPressed), RightPressed(rightPressed)
    {}
}
