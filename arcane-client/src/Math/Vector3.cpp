#include "Math/Vector3.h"

namespace Math
{
    Vector3& Vector3::operator=(const DirectX::XMVECTOR& vector) noexcept
    {
        X = DirectX::XMVectorGetX(vector);
        Y = DirectX::XMVectorGetY(vector);
        Z = DirectX::XMVectorGetZ(vector);

        return *this;
    }

    Vector3::operator DirectX::XMVECTOR() const
    {
        return DirectX::XMVectorSet(X, Y, Z, 0.0f);
    }
}