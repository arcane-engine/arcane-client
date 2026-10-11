#pragma once

#include "RenderContext.h"
#include "Graphics/Device.h"
#include "Graphics/RenderPipeline.h"
#include "Graphics/RenderQueue.h"

namespace Resources
{
    class ResourceManager;
}

namespace Graphics
{
    class RenderSystem
    {
    public:
        RenderSystem(HWND hWnd, int width, int height);

        [[nodiscard]] Device& GetDevice();
        [[nodiscard]] RenderQueue& GetRenderQueue();

        void BuildRenderPipeline(Resources::ResourceManager& resourceManager);
        void ClearRenderQueue() noexcept;
        void ExecuteRenderPipeline(RenderContext& renderContext);

    private:
        Device _device;
        RenderPipeline _renderPipeline;
        RenderQueue _renderQueue;
    };
}
