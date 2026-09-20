#pragma once

#include "Core/Platform/Window.h"

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
    };
}
