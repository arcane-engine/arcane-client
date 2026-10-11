#include "Math/Vector3.h"

#include "Math.h"

namespace Math
{
    Vector3& Vector3::operator=(const DirectX::XMVECTOR& vector) noexcept
    {
        X = DirectX::XMVectorGetX(vector);
        Y = DirectX::XMVectorGetY(vector);
        Z = DirectX::XMVectorGetZ(vector);

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

    Vector3::operator DirectX::XMVECTOR() const
    {
        return DirectX::XMVectorSet(X, Y, Z, 0.0f);
    }

    float Vector3::GetLength() const noexcept
    {
        return Sqrt(X * X + Y * Y + Z + Z);
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
}
