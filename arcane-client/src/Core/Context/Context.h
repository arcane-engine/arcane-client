#pragma once

#include "Core/Context/CameraContext.h"
#include "Core/Context/InputContext.h"
#include "Core/Context/TimeContext.h"

namespace Core
{
    struct Context
    {
        TimeContext Time;
        InputContext Input;
        CameraContext Camera;
    };
}
