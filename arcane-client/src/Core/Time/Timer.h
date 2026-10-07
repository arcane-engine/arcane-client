#pragma once

#include <chrono>

namespace Core
{
    class Timer final
    {
    public:
        Timer() noexcept;
        ~Timer() = default;

        Timer(const Timer&) = delete;
        Timer& operator=(const Timer&) = delete;
        Timer(Timer&&) = delete;
        Timer& operator=(Timer&& timer) = delete;

        void Update() noexcept;

        [[nodiscard]] float GetNow() const noexcept;
        [[nodiscard]] float GetDelta() const noexcept;
        [[nodiscard]] float GetSmoothDelta() const noexcept;

    private:
        std::chrono::steady_clock::time_point _start;
        float _now = 0.0f;
        float _delta = 0.0f;
        float _smoothDelta = 0.0f;
    };
}
