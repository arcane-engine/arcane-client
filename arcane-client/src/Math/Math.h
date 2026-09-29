#pragma once

#define PI 3.14159265358979323846f
#define EPSILON 0.001f
#define EPSILON_SQUARED 0.000001f
#define FLOAT_MIN (-3.402823466e+38F)
#define FLOAT_MAX 3.402823466e+38F

namespace Math
{
    [[nodiscard]] float Clamp(float value, float min, float max) noexcept;
    [[nodiscard]] float Sin(float value) noexcept;
    [[nodiscard]] float Cos(float value) noexcept;
}
