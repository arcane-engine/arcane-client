#include "ObjectTransformBuffer.h"

#include "Graphics/RenderContext.h"

namespace Graphics
{
    ObjectTransformBuffer::ObjectTransformBuffer(const DirectX::XMMATRIX& worldMatrix, const DirectX::XMMATRIX& worldViewProjectionMatrix) noexcept
        : WorldMatrix(worldMatrix), WorldViewProjectionMatrix(worldViewProjectionMatrix)
    {}

    ObjectTransformBuffer ObjectTransformBuffer::FromRenderContext(const RenderContext& renderContext) noexcept
    {
        return {
            DirectX::XMMatrixTranspose(renderContext.WorldMatrix),
            DirectX::XMMatrixTranspose(renderContext.WorldViewProjectionMatrix)
        };
    }
}
