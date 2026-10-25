#include "Quaternion.h"

namespace Math
{
    Quaternion::Quaternion(const float x, const float y, const float z, const float w) noexcept
        : X(x), Y(y), Z(z), W(w)
    {}

    Quaternion::Quaternion(const std::array<float, 4>& array) noexcept
        : X(array[0]), Y(array[1]), Z(array[2]), W(array[3])
    {}

    Quaternion& Quaternion::operator=(const DirectX::XMVECTOR& vector) noexcept
    {
        X = DirectX::XMVectorGetX(vector);
        Y = DirectX::XMVectorGetY(vector);
        Z = DirectX::XMVectorGetZ(vector);
        W = DirectX::XMVectorGetW(vector);

        return *this;
    }

    Quaternion& Quaternion::operator=(const std::array<float, 4>& array) noexcept
    {
        X = array[0];
        Y = array[1];
        Z = array[2];
        W = array[3];

        return *this;
    }

    Quaternion::operator DirectX::XMVECTOR() const
    {
        return DirectX::XMVectorSet(X, Y, Z, W);
    }

    DirectX::XMMATRIX Quaternion::GetRotationMatrix() const noexcept
    {
        return DirectX::XMMatrixRotationQuaternion(DirectX::XMVectorSet(X, Y, Z, W));
    }
}
