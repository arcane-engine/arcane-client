#pragma once

namespace Network
{
    struct ClientInputPacket
    {
        bool Forward;
        bool Backward;
        bool Left;
        bool Right;

        auto operator==(const ClientInputPacket&) const -> bool = default;
    };
}
