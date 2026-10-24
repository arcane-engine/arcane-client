#pragma once

namespace Core
{
    struct MouseInputContext
    {
        bool Changed = false;
        bool LeftPressed = false;
        bool RightPressed = false;
        float DeltaX = 0.0f;
        float DeltaY = 0.0f;
        float WheelDelta = 0.0f;

        auto operator==(const MouseInputContext& input) const
        {
            return input.LeftPressed == LeftPressed && input.RightPressed == RightPressed && input.DeltaX == DeltaX && input.DeltaY == DeltaY;
        }
    };
}
