#include "Graphics/RenderResource/Data/ObjectTransformBuffer.h"

#include "Core/Context/Context.h"

namespace Graphics
{
    ObjectTransformBuffer::ObjectTransformBuffer(const DirectX::XMMATRIX& worldMatrix, const DirectX::XMMATRIX& worldViewProjectionMatrix) noexcept
        : WorldMatrix(worldMatrix), WorldViewProjectionMatrix(worldViewProjectionMatrix)
    {}

    ObjectTransformBuffer ObjectTransformBuffer::FromContext(const Core::Context& context) noexcept
    {
        return {
            DirectX::XMMatrixTranspose(context.Object.WorldMatrix),
            DirectX::XMMatrixTranspose(context.Object.WorldViewProjectionMatrix)
        };
    }
}
