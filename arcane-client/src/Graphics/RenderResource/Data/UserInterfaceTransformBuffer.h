#pragma once

#include <DirectXMath.h>

namespace Core
{
    struct Context;
}

namespace Graphics
{
    struct UserInterfaceTransformBuffer
    {
        DirectX::XMMATRIX WorldMatrix;

        UserInterfaceTransformBuffer() = default;
        explicit UserInterfaceTransformBuffer(const DirectX::XMMATRIX& worldMatrix) noexcept;

        static UserInterfaceTransformBuffer FromContext(const Core::Context& context) noexcept;
    };
}
