#pragma once

#include <DirectXMath.h>
#include <vector>

#include "Graphics/RenderQueue/RenderCommand.h"

namespace Core
{
    struct Context;
}

namespace Graphics
{
    class Device;
    class RenderObject;

    class RenderQueue
    {
    public:
        void Clear() noexcept;

        [[nodiscard]] const std::vector<RenderCommand>& GetCommands() noexcept;

        void Add(const RenderObject& object) noexcept;
        void Add(const RenderObject& object, const DirectX::XMMATRIX& worldMatrix) noexcept;
        void Add(const RenderObject& object, std::span<const DirectX::XMMATRIX> worldMatrixInstances) noexcept;

    private:
        std::vector<RenderCommand> _commands;
    };
}
