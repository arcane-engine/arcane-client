#include "Quaternion.h"

namespace Math
{
    Quaternion::operator DirectX::XMVECTOR() const
    {
        return DirectX::XMVectorSet(X, Y, Z, W);
    }
}
