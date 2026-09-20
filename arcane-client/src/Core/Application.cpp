#include "Core/Application.h"

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
            _window.SetTitle(L"Key is down!");
        }
        if (_window.GetKeyboard().IsKeyPressed('S'))
        {
            _window.SetTitle(L"Key is pressed!");
        }
    }
}
