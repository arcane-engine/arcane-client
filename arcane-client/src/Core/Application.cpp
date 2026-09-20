#include "Core/Application.h"

#include <format>

namespace Core
{
    Application::Application(const int width, const int height) :
        _window(width, height)
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
        if (_window.GetKeyboard().IsKeyDown('A'))
        {
            _window.SetTitle(L"Key is down");
        }
        if (_window.GetKeyboard().IsKeyPressed('S'))
        {
            _window.SetTitle(L"Key is pressed");
        }
        if (_window.GetMouse().IsLeftPressed())
        {
            _window.SetTitle(L"Left is pressed");
        }
        if (_window.GetMouse().IsRightPressed())
        {
            _window.SetTitle(L"Right is pressed");
        }
        while (const auto event = _window.GetMouse().ReadRawEvent())
        {
            const auto x = _window.GetMouse().GetSmoothDeltaX(static_cast<float>(event->GetX()));
            const auto y = _window.GetMouse().GetSmoothDeltaY(static_cast<float>(event->GetY()));

            _window.SetTitle(std::format(L"X: {:.6f}, Y: {:.6f}", x, y));
        }

    }
}
