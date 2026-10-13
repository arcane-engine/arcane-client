#include "Core/Time/TimeSystem.h"

#include <chrono>

namespace Core
{
    TimeSystem::TimeSystem() noexcept
        : _start(std::chrono::steady_clock::now())
    {}

    TimeContext TimeSystem::Update() noexcept
    {
        const auto now = std::chrono::duration<float>(std::chrono::steady_clock::now() - _start).count();
        const auto delta = now - _now;

        _smoothDelta = _smoothDelta * 0.98f + delta * 0.02f;
        _now = now;

        return {
            .Now = _now,
            .Delta = delta,
            .SmoothDelta = _smoothDelta
        };
    }
}
