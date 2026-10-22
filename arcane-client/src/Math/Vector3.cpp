#include "Math/Vector3.h"

#include "Math/Math.h"

namespace Math
{
    Vector3::Vector3(const float x, const float y, const float z) noexcept
    : X(x), Y(y), Z(z)
    {}

    Vector3::Vector3(const std::array<float, 3>& array) noexcept
        : X(array[0]), Y(array[1]), Z(array[2])
    {}

    Vector3& Vector3::operator=(const DirectX::XMVECTOR& vector) noexcept
    {
        X = DirectX::XMVectorGetX(vector);
        Y = DirectX::XMVectorGetY(vector);
        Z = DirectX::XMVectorGetZ(vector);

        return *this;
    }

    Vector3& Vector3::operator=(const std::array<float, 3>& array) noexcept
    {
        X = array[0];
        Y = array[1];
        Z = array[2];

        return *this;
    }

    Vector3 Vector3::operator*(const float value) const noexcept
    {
        return { X * value, Y * value, Z * value };
    }

    Vector3 Vector3::operator+(const Vector3& value) const noexcept
    {
        return { X + value.X, Y + value.Y, Z + value.Z };
    }

    Vector3 Vector3::operator-(const Vector3& value) const noexcept
    {
        return { X - value.X, Y - value.Y, Z - value.Z };
    }

    Vector3::operator DirectX::XMVECTOR() const
    {
        return DirectX::XMVectorSet(X, Y, Z, 0.0f);
    }

    float Vector3::GetLength() const noexcept
    {
        return Sqrt(X * X + Y * Y + Z * Z);
    }

    Vector3 Vector3::GetNormalized() const noexcept
    {
        const auto length = GetLength();

        if (length > 0.0f)
        {
            return { X / length, Y / length, Z / length };
        }

        return { 0.0f, 0.0f, 0.0f };
    }

    void Vector3::Normalize() noexcept
    {
        const auto length = GetLength();

        if (length > 0.0f)
        {
            X = X / length;
            Y = Y / length;
            Z = Z / length;
        }
    }
}
