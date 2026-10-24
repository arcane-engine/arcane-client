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
            packet.ActorSetup = ServerActorSetupPacket
            {
                .Id = reader.ReadUnsignedShort()
            };
        }
        if (reader.ReadBit())
        {
            const auto count = reader.ReadUnsignedShort();
            for (std::uint16_t i = 0; i < count; i++)
            {
                packet.ActorRegister.push_back(ServerActorRegisterPacket
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
                    .Position = reader.ReadFloat3(),
                    .Velocity = reader.ReadFloat3()
                });
            }
        }
        if (reader.ReadBit())
        {
            const auto count = reader.ReadUnsignedShort();
            for (std::uint16_t i = 0; i < count; i++)
            {
                packet.SceneNodes.push_back(ServerSceneNodePacket
                {
                    .Id = reader.ReadUnsignedShort(),
                    .Mesh = reader.ReadString(),
                    .Material = reader.ReadString(),
                    .Position = reader.ReadFloat3(),
                    .Rotation = reader.ReadFloat4(),
                    .Scale = reader.ReadFloat3()
                });
            }
        }

        return packet;
    }
}
