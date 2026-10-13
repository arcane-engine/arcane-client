#pragma once

#include "Core/Context/InputContext.h"
#include "Platform/Window.h"

namespace Core::Input
{
    class InputSystem
    {
    public:
        [[nodiscard]] InputContext Update(Platform::Window& window);

    private:
        InputContext _input{};
    };
}
