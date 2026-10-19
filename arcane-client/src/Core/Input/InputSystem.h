#pragma once

#include "Core/Context/InputContext.h"
#include "Platform/Window.h"

namespace Core
{
    struct Context;
}

namespace Core::Input
{
    class InputSystem
    {
    public:
        void Update(Platform::Window& window, Context& context);

    private:
        InputContext _input{};
    };
}
