#pragma once

#include <cstdint>
#include <vector>

namespace Network
{
    struct ServerRegisterPacket
    {
        bool Register;
        std::uint16_t Id;
    };

    struct ServerPacket
    {
        std::vector<ServerRegisterPacket> Register;
    };
}
