#include "Network/Protocol/ServerPacketReader.h"

#include "Core/IO/BitReader.h"

namespace Network
{
    ServerPacket ServerPacketReader::Read(const std::uint8_t* buffer)
    {
        auto reader = Core::IO::BitReader(buffer);

        auto packet = ServerPacket();

        if (reader.ReadBit())
        {
            const auto count = reader.ReadUnsignedShort();
            for (std::uint16_t i = 0; i < count; i++)
            {
                packet.Actor.push_back(ServerActorPacket
                {
                    .Register = reader.ReadBit(),
                    .Id = reader.ReadUnsignedShort()
                });
            }
        }

        return packet;
    }
}
