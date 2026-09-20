#pragma once

#include "Core/Platform/Window.h"

namespace Core
{
    class Application
    {
    public:
        Application(int width, int height);

        int32_t Run();

    private:
        Platform::Window _window;
    };
}
