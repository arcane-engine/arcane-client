#pragma once

#include "Core/Context/KeybordInputContext.h"
#include "Core/Context/MouseInputContext.h"

namespace Core
{
    struct InputContext
    {
        KeybordInputContext Keyboard;
        MouseInputContext Mouse;
    };
}
