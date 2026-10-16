#pragma once

#include <cstdint>
#include <vector>

namespace Network
{
    struct ServerActorPacket
    {
        bool Register;
        std::uint16_t Id;
    };

    struct ServerPacket
    {
        std::vector<ServerActorPacket> Actor;
    };
}
