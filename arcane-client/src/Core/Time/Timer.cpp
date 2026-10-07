#include "Timer.h"

#include <chrono>

namespace Core
{
    Timer::Timer() noexcept
        : _start(std::chrono::steady_clock::now())
    {}

    void Timer::Update() noexcept
    {
        const auto now = std::chrono::duration<float>(std::chrono::steady_clock::now() - _start).count();

        _delta = now - _now;
        _smoothDelta = _smoothDelta * 0.98f + _delta * 0.02f;
        _now = now;
    }

    float Timer::GetNow() const noexcept
    {
        return _now;
    }

    float Timer::GetDelta() const noexcept
    {
        return _delta;
    }

    float Timer::GetSmoothDelta() const noexcept
    {
        return _smoothDelta;
    }
}
