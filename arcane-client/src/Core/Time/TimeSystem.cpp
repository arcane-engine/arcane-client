#include "Core/Time/TimeSystem.h"

#include <chrono>

#include "Core/Context/Context.h"

namespace Core
{
    TimeSystem::TimeSystem() noexcept
        : _start(std::chrono::steady_clock::now())
    {}

    void TimeSystem::Update(Context& context) noexcept
    {
        context.Time.Now = std::chrono::duration<float>(std::chrono::steady_clock::now() - _start).count();
        context.Time.Delta = context.Time.Now - _now;
        context.Time.SmoothDelta = _smoothDelta * 0.98f + context.Time.Delta * 0.02f;

        _now = context.Time.Now;
        _smoothDelta = context.Time.SmoothDelta;
    }
}
