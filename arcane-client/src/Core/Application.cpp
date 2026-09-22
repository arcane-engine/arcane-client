#include "Core/Application.h"

namespace Core
{
    Application::Application(const int width, const int height) :
        _window(width, height),
        _device(_window.GetDevice())
    {
        _renderPipeline.Build(_device);
    }

    int Application::Run()
    {
        while (true)
        {
            if (const auto exitCode = _window.ProcessMessages())
            {
                return static_cast<int>(*exitCode);
            }

            Update();
        }
    }

    void Application::Update()
    {
        _renderPipeline.Execute(_device);
    }
}
