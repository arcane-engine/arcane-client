#pragma once

#include <DirectXMath.h>
#include <vector>

#include "Graphics/RenderQueue/RenderCommand.h"

namespace Graphics
{
    class RenderContext;
    class Device;
    class RenderObject;

    class RenderQueue
    {
    public:
        void Clear() noexcept;

        void Add(const RenderObject& object);
        void Add(const RenderObject& object, const DirectX::XMMATRIX& worldMatrix);

        void Execute(Device& device, RenderContext& renderContext) const noexcept;

    private:
        std::vector<RenderCommand> _commands;
    };
}
