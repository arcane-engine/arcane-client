#include "CameraTransformBuffer.h"

namespace Graphics
{
    CameraTransformBuffer::CameraTransformBuffer(const DirectX::XMMATRIX& viewMatrix, const DirectX::XMMATRIX& projectionMatrix) noexcept
        : ViewMatrix(viewMatrix), ProjectionMatrix(projectionMatrix)
    {}
}
