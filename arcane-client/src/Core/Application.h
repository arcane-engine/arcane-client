#pragma once

#include "Core/Platform/Window.h"
#include "Graphics/Device.h"
#include "Graphics/RenderPipeline.h"

namespace Core
{
    class Application
    {
    public:
        Application(int width, int height);

        int Run();

    private:
        void Update();

        Platform::Window _window;
        Graphics::Device& _device;
        Graphics::RenderPipeline _renderPipeline;
    };
}
