#include "Core/Input/KeyboardEvent.h"

namespace Core::Input
{
    KeyboardEvent::KeyboardEvent(const Type type, const std::uint8_t keyCode) noexcept
        : _type(type), _keyCode(keyCode)
    {}

    bool KeyboardEvent::IsKeyDown() const noexcept
    {
        return _type == Type::KeyDown;
    }

    bool KeyboardEvent::IsKeyUp() const noexcept
    {
        return _type == Type::KeyUp;
    }

    std::uint8_t KeyboardEvent::GetKeyCode() const noexcept
    {
        return _keyCode;
    }
}
