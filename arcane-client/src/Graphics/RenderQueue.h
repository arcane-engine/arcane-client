#pragma once

#include <DirectXMath.h>
#include <vector>

#include "Graphics/RenderQueue/RenderCommand.h"

namespace Graphics
{
    class Device;
    class RenderContext;
    class RenderObject;

    class RenderQueue
    {
    public:
        void Clear() noexcept;

        void Add(const RenderObject& object) noexcept;
        void Add(const RenderObject& object, const DirectX::XMMATRIX& worldMatrix) noexcept;
        void Add(const RenderObject& object, std::span<const DirectX::XMMATRIX> instanceMatrices) noexcept;

        void Execute(Device& device, RenderContext& renderContext) const noexcept;

    private:
        std::vector<RenderCommand> _commands;
    };
}
