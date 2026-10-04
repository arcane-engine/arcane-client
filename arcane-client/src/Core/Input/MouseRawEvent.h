#pragma once

namespace Core::Input
{
    struct  MouseRawEvent
    {
        int X;
        int Y;

        MouseRawEvent(int x, int y) noexcept;
    };
}
