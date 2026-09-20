#include "Core/Application.h"

namespace Core
{
    Application::Application(const int width, const int height) :
        _window(width, height)
    {}

    int32_t Application::Run()
    {
        while (true)
        {
            if (const auto exitCode = _window.ProcessMessages())
            {
                return static_cast<int32_t>(*exitCode);
            }
        }
    }
}