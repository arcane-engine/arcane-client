#include "Math/Ray.h"

namespace Math
{
    Ray::Ray(const Vector3 origin, const Vector3 direction) noexcept
        : Origin(origin), Direction(direction)
    {}
}
