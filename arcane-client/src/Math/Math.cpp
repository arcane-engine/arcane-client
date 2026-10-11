#include "Math/Math.h"

#include <algorithm>
#include <complex>

namespace Math
{
    float Clamp(const float value, const float min, const float max) noexcept
    {
        return std::clamp(value, min, max);
    }

    float Sin(const float value) noexcept
    {
        return std::sinf(value);
    }

    float Cos(const float value) noexcept
    {
        return std::cosf(value);
    }

    float Sqrt(const float value) noexcept
    {
        return std::sqrtf(value);
    }

    size_t Max(const size_t v1, const size_t v2)
    {
        return std::max(v1, v2);
    }
}
