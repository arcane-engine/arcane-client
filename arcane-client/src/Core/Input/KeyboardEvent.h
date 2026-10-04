#pragma once

#include <cstdint>

namespace Core::Input
{
    enum class KeyboardEventType : std::uint8_t
    {
        KeyDown,
        KeyUp,
    };

    struct KeyboardEvent
    {
        KeyboardEventType Type;
        std::uint8_t KeyCode;

        KeyboardEvent(KeyboardEventType type, std::uint8_t keyCode) noexcept;

        [[nodiscard]] bool IsKeyDown() const noexcept;
        [[nodiscard]] bool IsKeyUp() const noexcept;
    };
}
