#pragma once

#include <cstdint>

namespace Core::Input
{
    class KeyboardEvent
    {
    public:
        enum class Type : std::uint8_t
        {
            KeyDown,
            KeyUp,
        };

        KeyboardEvent(Type type, std::uint8_t keyCode) noexcept;

        [[nodiscard]] bool IsKeyDown() const noexcept;
        [[nodiscard]] bool IsKeyUp() const noexcept;
        [[nodiscard]] std::uint8_t GetKeyCode() const noexcept;

    private:
        Type _type;
        std::uint8_t _keyCode;
    };
}
