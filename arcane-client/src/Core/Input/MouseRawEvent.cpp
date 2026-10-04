#include "Core/Input/MouseRawEvent.h"

namespace Core::Input
{
    MouseRawEvent::MouseRawEvent(const int x, const int y) noexcept
        : X(x), Y(y)
    {}
}
