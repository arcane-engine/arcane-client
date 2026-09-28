#pragma once

#include "Math/Math.h"

namespace Graphics
{
    class CameraRotation
    {
    public:
        explicit CameraRotation(float min = FLOAT_MIN, float max = FLOAT_MAX) noexcept;

        [[nodiscard]] float GetValue() const noexcept;

        void Rotate(float value) noexcept;

    private:
        float _min;
        float _max;
        float _value;
    };
}

