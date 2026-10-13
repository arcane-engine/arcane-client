#pragma once

#include <chrono>

#include "Core/Context/TimeContext.h"

namespace Core
{
    class TimeSystem final
    {
    public:
        TimeSystem() noexcept;
        ~TimeSystem() = default;

        TimeSystem(const TimeSystem&) = delete;
        TimeSystem& operator=(const TimeSystem&) = delete;
        TimeSystem(TimeSystem&&) = delete;
        TimeSystem& operator=(TimeSystem&& timer) = delete;

        [[nodiscard]] TimeContext Update() noexcept;

    private:
        std::chrono::steady_clock::time_point _start;
        float _now = 0.0f;
        float _smoothDelta = 0.0f;
    };
}
