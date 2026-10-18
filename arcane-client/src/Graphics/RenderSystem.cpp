#include "Graphics/RenderSystem.h"

#include "Resources/ResourceManager.h"

namespace Graphics
{
    RenderSystem::RenderSystem(const HWND hWnd, const int width, const int height)
        : _device(hWnd, width, height)
    {}

    Device& RenderSystem::GetDevice()
    {
        return _device;
    }

    void RenderSystem::BuildRenderPipeline(Resources::ResourceManager& resourceManager)
    {
        _renderPipeline.Build(_device, resourceManager.GetShaderLibrary(), resourceManager.GetSamplerLibrary(), resourceManager.GetDepthStencilStateLibrary(), resourceManager.GetInputLayoutLibrary());
    }

    void RenderSystem::ExecuteRenderPipeline(Core::Context& context)
    {
        _renderPipeline.Execute(_device, context);
    }
}
