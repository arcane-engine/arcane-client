#pragma once

#include "Graphics/Device.h"
#include "Graphics/RenderPipeline.h"
#include "Graphics/RenderQueue.h"

namespace Core
{
    struct Context;
}

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

        void BuildRenderPipeline(Resources::ResourceManager& resourceManager);
        void ExecuteRenderPipeline(Core::Context& context);

    private:
        Device _device;
        RenderPipeline _renderPipeline;
        RenderQueue _renderQueue;
    };
}
