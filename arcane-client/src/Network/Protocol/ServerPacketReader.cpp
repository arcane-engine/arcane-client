#include "Network/Protocol/ServerPacketReader.h"

#include "Core/IO/BitReader.h"
#include "Packets/ServerPacket.h"

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
                    .Id = reader.ReadUnsignedShort(),
                    .Register = reader.ReadBit()
                });
            }
        }
        if (reader.ReadBit())
        {
            const auto count = reader.ReadUnsignedShort();
            for (std::uint16_t i = 0; i < count; i++)
            {
                packet.ActorMotion.push_back(ServerActorMotionPacket
                {
                    .Id = reader.ReadUnsignedShort(),
                    .Position = {
                        .X = reader.ReadFloat(),
                        .Y = reader.ReadFloat(),
                        .Z = reader.ReadFloat()
                    },
                    .Velocity = {
                        .X = reader.ReadFloat(),
                        .Y = reader.ReadFloat(),
                        .Z = reader.ReadFloat()
                    }
                });
            }
        }

        return packet;
    }
}
