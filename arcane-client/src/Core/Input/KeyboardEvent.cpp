#include "Core/Input/KeyboardEvent.h"

namespace Core::Input
{
    KeyboardEvent::KeyboardEvent(const KeyboardEventType type, const std::uint8_t keyCode) noexcept
        : Type(type), KeyCode(keyCode)
    {}

    bool KeyboardEvent::IsKeyDown() const noexcept
    {
        return Type == KeyboardEventType::KeyDown;
    }

    bool KeyboardEvent::IsKeyUp() const noexcept
    {
        return Type == KeyboardEventType::KeyUp;
    }
}
