#include "Math.h"

#include <algorithm>

namespace Math
{
    float Clamp(const float value, const float min, const float max) noexcept
    {
        return std::clamp(value, min, max);
    }
}
