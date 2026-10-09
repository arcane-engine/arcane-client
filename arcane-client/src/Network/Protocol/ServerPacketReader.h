#pragma once
#include "Packets/ServerRegisterPacket.h"

namespace Network
{
    class ServerPacketReader
    {
    public:
        [[nodiscard]] static ServerPacket Read(const std::uint8_t* buffer);
    };
}
