#include "UserInterfaceTransformBuffer.h"

#include "Core/Context/Context.h"

namespace Graphics
{
    UserInterfaceTransformBuffer::UserInterfaceTransformBuffer(const DirectX::XMMATRIX& worldMatrix) noexcept
        : WorldMatrix(worldMatrix)
    {}

    UserInterfaceTransformBuffer UserInterfaceTransformBuffer::FromContext(const Core::Context& context) noexcept
    {
        return UserInterfaceTransformBuffer(DirectX::XMMatrixTranspose(context.Object.WorldMatrix));
    }
}
