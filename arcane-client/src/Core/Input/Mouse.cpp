#include "Core/Input/Mouse.h"

#include <windows.h>

namespace Core::Input
{
    Mouse::Mouse(const int width, const int height)
        : _width(width), _height(height)
    {}

    int Mouse::GetX() const noexcept
    {
        return _x;
    }

    int Mouse::GetY() const noexcept
    {
        return _y;
    }

    float Mouse::GetNormalizedX() const noexcept
    {
        return 2.0f * static_cast<float>(_x) / static_cast<float>(_width) - 1.0f;
    }

    float Mouse::GetNormalizedY() const noexcept
    {
        return -2.0f * static_cast<float>(_y) / static_cast<float>(_height) + 1.0f;
    }

    bool Mouse::IsInWindow() const noexcept
    {
        return _inWindow;
    }

    bool Mouse::IsLeftPressed() const noexcept
    {
        return _leftPressed;
    }

    bool Mouse::IsRightPressed() const noexcept
    {
        return _rightPressed;
    }

    std::optional<MouseEvent> Mouse::ReadEvent() noexcept
    {
        if (_eventBuffer.empty())
        {
            return {};
        }

        const auto& result = _eventBuffer.front();
        _eventBuffer.pop();

        return result;
    }

    std::optional<MouseRawEvent> Mouse::ReadRawEvent() noexcept
    {
        if (_rawEventBuffer.empty())
        {
            return {};
        }

        const auto& result = _rawEventBuffer.front();
        _rawEventBuffer.pop();

        return result;
    }

    bool Mouse::IsEmpty() const noexcept
    {
        return _eventBuffer.empty();
    }

    float Mouse::GetSmoothDelta(const float value) noexcept
    {
        _smoothDeltaX = _smoothDeltaX * (1.0f - _smoothAlpha) + value * _smoothAlpha;

        return _smoothDeltaX / 600.0f;
    }

    void Mouse::Flush() noexcept
    {
        _eventBuffer = std::queue<MouseEvent>();
        _rawEventBuffer = std::queue<MouseRawEvent>();
    }

    void Mouse::OnMove(const int x, const int y)
    {
        _x = x;
        _y = y;

        _eventBuffer.emplace(MouseEventType::Move, _x, _y, false, false);

        TrimEventBuffer();
    }

    void Mouse::OnMoveRaw(const int x, const int y)
    {
        _rawEventBuffer.emplace(x, y);

        TrimRawEventBuffer();
    }

    void Mouse::OnEnter()
    {
        _inWindow = true;

        _eventBuffer.emplace(MouseEventType::Enter, _x, _y, false, false);

        TrimEventBuffer();
    }

    void Mouse::OnLeave()
    {
        _inWindow = false;

        _eventBuffer.emplace(MouseEventType::Leave, _x, _y, false, false);

        TrimEventBuffer();
    }

    void Mouse::OnLeftPressed(int x, int y)
    {
        _leftPressed = true;

        _eventBuffer.emplace(MouseEventType::LeftDown, x, y, true, false);

        TrimEventBuffer();
    }

    void Mouse::OnLeftReleased(int x, int y)
    {
        _leftPressed = false;

        _eventBuffer.emplace(MouseEventType::LeftUp, x, y, false, false);

        TrimEventBuffer();
    }

    void Mouse::OnRightPressed(int x, int y)
    {
        _rightPressed = true;

        _eventBuffer.emplace(MouseEventType::RightDown, x, y, false, true);

        TrimEventBuffer();
    }

    void Mouse::OnRightReleased(int x, int y)
    {
        _rightPressed = false;

        _eventBuffer.emplace(MouseEventType::RightUp, x, y, false, false);

        TrimEventBuffer();
    }

    void Mouse::OnWheelUp(int x, int y)
    {
        _eventBuffer.emplace(MouseEventType::WheelUp, x, y, false, false);

        TrimEventBuffer();
    }

    void Mouse::OnWheelDown(int x, int y)
    {
        _eventBuffer.emplace(MouseEventType::WheelDown, x, y, false, false);

        TrimEventBuffer();
    }

    void Mouse::OnWheelDelta(const int x, const int y, const int delta)
    {
        _wheelDelta = _wheelDelta + delta;

        while (_wheelDelta >= WHEEL_DELTA)
        {
            _wheelDelta = _wheelDelta - WHEEL_DELTA;
            OnWheelUp(x, y);
        }
        while (_wheelDelta <= -WHEEL_DELTA)
        {
            _wheelDelta = _wheelDelta + WHEEL_DELTA;
            OnWheelDown(x, y);
        }
    }

    void Mouse::TrimEventBuffer()
    {
        while (_eventBuffer.size() > 16)
        {
            _eventBuffer.pop();
        }
    }

    void Mouse::TrimRawEventBuffer()
    {
        while (_rawEventBuffer.size() > 16)
        {
            _rawEventBuffer.pop();
        }
    }
}
