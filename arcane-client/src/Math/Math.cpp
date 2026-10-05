#include "Math/Math.h"

#include <algorithm>

namespace Math
{
    float Clamp(const float value, const float min, const float max) noexcept
    {
        return std::clamp(value, min, max);
    }

    float Sin(const float value) noexcept
    {
        return sinf(value);
    }

    float Cos(const float value) noexcept
    {
        return cosf(value);
    }

    size_t Max(const size_t v1, const size_t v2)
    {
        return std::max(v1, v2);
    }
}
