#pragma once

#include <bitset>
#include <optional>
#include <queue>

#include "Core/Input/KeyboardEvent.h"

namespace Platform
{
    class Window;
}

namespace Core::Input
{
    class Keyboard
    {
        friend class Platform::Window;

    public:
        Keyboard() = default;
        ~Keyboard() = default;

        Keyboard(const Keyboard&) = delete;
        Keyboard& operator=(const Keyboard&) = delete;
        Keyboard(Keyboard&&) = delete;
        Keyboard& operator=(Keyboard&& keyboard) = delete;

        [[nodiscard]] bool IsKeyDown(std::uint8_t key) const noexcept;
        [[nodiscard]] bool IsKeyPressed(std::uint8_t key) noexcept;

        [[nodiscard]] std::optional<KeyboardEvent> ReadEvent() noexcept;

        void ClearState() noexcept;

    private:
        void OnKeyDown(std::uint8_t key);
        void OnKeyUp(std::uint8_t key);
        void TrimBuffer();

        static constexpr std::size_t _bufferSize = 16;

        std::bitset<256> _keyState;
        std::bitset<256> _keyDown;
        std::queue<KeyboardEvent> _buffer;
    };
}
