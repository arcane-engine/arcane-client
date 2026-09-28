#include "ObjectTransformBuffer.h"

namespace Graphics
{
    ObjectTransformBuffer::ObjectTransformBuffer(const DirectX::XMMATRIX& worldMatrix, const DirectX::XMMATRIX& worldViewProjectionMatrix) noexcept
        : WorldMatrix(worldMatrix), WorldViewProjectionMatrix(worldViewProjectionMatrix)
    {}
}
