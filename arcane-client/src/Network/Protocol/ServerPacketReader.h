#pragma once
#include "Packets/ServerActorPacket.h"

namespace Network
{
    class ServerPacketReader
    {
    public:
        [[nodiscard]] static ServerPacket Read(const std::uint8_t* buffer);
    };
}
