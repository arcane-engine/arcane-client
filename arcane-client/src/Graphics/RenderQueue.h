#pragma once

#include <DirectXMath.h>
#include <vector>

#include "Graphics/RenderQueue/RenderCommand.h"

namespace Graphics
{
    class Device;
    class RenderObject;

    class RenderQueue
    {
    public:
        void Clear() noexcept;

        void Add(const RenderCommand& command);
        void Add(const RenderObject& object, const DirectX::XMMATRIX& transform);

        void Execute(const Device& device) const noexcept;

    private:
        std::vector<RenderCommand> _commands;
    };
}
