#include "Graphics/RenderQueue.h"
#include "Graphics/RenderObject.h"

#include <DirectXMath.h>

namespace Graphics
{
    void RenderQueue::Clear() noexcept
    {
        _commands.clear();
    }

    void RenderQueue::Add(const RenderCommand& command)
    {
        _commands.push_back(command);
    }

    void RenderQueue::Add(const RenderObject& object, const DirectX::XMMATRIX& transform)
    {
        _commands.push_back(RenderCommand(object, transform));
    }

    void RenderQueue::Execute(const Device& device) const noexcept
    {
        for (const auto& command : _commands)
        {
            command.GetRenderObject().Bind(device);
            command.GetRenderObject().Draw(device);
        }
    }
}