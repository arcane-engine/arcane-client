#include "Graphics/RenderResource/Data/CameraTransformBuffer.h"

#include "Core/Context/Context.h"

namespace Graphics
{
    CameraTransformBuffer::CameraTransformBuffer(const DirectX::XMMATRIX& viewMatrix, const DirectX::XMMATRIX& projectionMatrix) noexcept
        : ViewMatrix(viewMatrix), ProjectionMatrix(projectionMatrix)
    {}

    CameraTransformBuffer CameraTransformBuffer::FromContext(const Core::Context& context) noexcept
    {
        return {
            DirectX::XMMatrixTranspose(context.Camera.ViewMatrix),
            DirectX::XMMatrixTranspose(context.Camera.ProjectionMatrix)
        };
    }
}
