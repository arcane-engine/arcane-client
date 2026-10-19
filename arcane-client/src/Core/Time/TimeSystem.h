#pragma once

#include <chrono>

namespace Core
{
    struct Context;

    class TimeSystem final
    {
    public:
        TimeSystem() noexcept;
        ~TimeSystem() = default;

        TimeSystem(const TimeSystem&) = delete;
        TimeSystem& operator=(const TimeSystem&) = delete;
        TimeSystem(TimeSystem&&) = delete;
        TimeSystem& operator=(TimeSystem&& timer) = delete;

        void Update(Context& context) noexcept;

    private:
        std::chrono::steady_clock::time_point _start;
        float _now = 0.0f;
        float _smoothDelta = 0.0f;
    };
}
