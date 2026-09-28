#include "CameraRotation.h"

namespace Graphics
{
    CameraRotation::CameraRotation(const float min, const float max) noexcept
        : _min(min), _max(max), _value((min + max) / 2.0f)
    {
    }

    float CameraRotation::GetValue() const noexcept
    {
        return _value;
    }

    void CameraRotation::Rotate(const float value) noexcept
    {
        _value = Math::Clamp(_value + value, _min, _max);
    }
}
