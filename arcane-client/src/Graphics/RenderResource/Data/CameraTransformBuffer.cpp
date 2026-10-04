#include "Graphics/RenderResource/Data/CameraTransformBuffer.h"

#include "Graphics/RenderContext.h"

namespace Graphics
{
    CameraTransformBuffer::CameraTransformBuffer(const DirectX::XMMATRIX& viewMatrix, const DirectX::XMMATRIX& projectionMatrix) noexcept
        : ViewMatrix(viewMatrix), ProjectionMatrix(projectionMatrix)
    {}

    CameraTransformBuffer CameraTransformBuffer::FromRenderContext(const RenderContext& renderContext) noexcept
    {
        return {
            DirectX::XMMatrixTranspose(renderContext.ViewMatrix),
            DirectX::XMMatrixTranspose(renderContext.ProjectionMatrix)
        };
    }
}
