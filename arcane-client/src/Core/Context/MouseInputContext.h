#pragma once

namespace Core
{
    struct MouseInputContext
    {
        bool LeftPressed = false;
        bool RightPressed = false;
        float DeltaX = 0.0f;
        float DeltaY = 0.0f;
        float WheelDelta = 0.0f;
    };
}
