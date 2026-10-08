#pragma once

namespace Network
{
    struct ClientInputPacket
    {
        bool Forward;
        bool Backward;
        bool Left;
        bool Right;
    };
}
