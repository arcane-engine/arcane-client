#pragma once

#include "Math/Vector3.h"

namespace Math
{
    struct Ray
    {
        Vector3 Origin;
        Vector3 Direction;

        Ray() = default;
        Ray(Vector3 origin, Vector3 direction) noexcept;
    };
}
