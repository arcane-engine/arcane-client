#include "Core/Input/Keyboard.h"

#include <optional>

#include "Core/Input/KeyboardEvent.h"

namespace Core::Input
{
    void Keyboard::OnKeyDown(std::uint8_t key)
    {
        if (!_keyState[key])
        {
            _keyState[key] = true;
            _buffer.emplace(KeyboardEventType::KeyDown, key);
            TrimBuffer();
        }
    }

    void Keyboard::OnKeyUp(std::uint8_t key)
    {
        _keyState[key] = false;
        _keyDown[key] = false;
        _buffer.emplace(KeyboardEventType::KeyUp, key);
        TrimBuffer();
    }

    bool Keyboard::IsKeyDown(const std::uint8_t key) const noexcept
    {
        return _keyState[key];
    }

    bool Keyboard::IsKeyPressed(const std::uint8_t key) noexcept
    {
        if (_keyState[key] && !_keyDown[key])
        {
            _keyDown[key] = true;
            return true;
        }

        return false;
    }

    std::optional<KeyboardEvent> Keyboard::ReadEvent() noexcept
    {
        if (_buffer.empty())
        {
            return std::nullopt;
        }

        KeyboardEvent event = _buffer.front();
        _buffer.pop();
        return event;
    }

    void Keyboard::ClearState() noexcept
    {
        _keyState.reset();
        _keyDown.reset();
        _buffer = {};
    }

    void Keyboard::TrimBuffer()
    {
        while (_buffer.size() > _bufferSize)
        {
            _buffer.pop();
        }
    }
}
