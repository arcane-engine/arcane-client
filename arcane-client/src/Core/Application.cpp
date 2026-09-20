#include "Core/Application.h"

#include <format>

#include "Graphics/Buffer/RenderTarget.h"

namespace Core
{
    Application::Application(const int width, const int height) :
        _window(width, height),
        _device(_window.GetDevice())
    {}

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
        auto& rtv = _device.GetCompositeRenderTarget()->GetRenderTargetView();

        _device.GetDeviceContext()->OMSetRenderTargets(1, rtv.GetAddressOf(), nullptr);

        _device.GetCompositeRenderTarget()->Clear();

        _device.GetSwapChain()->Present(1, 0);
    }
}
