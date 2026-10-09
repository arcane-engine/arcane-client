#include "ServerPacketReader.h"

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
                packet.Register.push_back(ServerRegisterPacket
                {
                    .Register = reader.ReadBit(),
                    .Id = reader.ReadUnsignedShort()
                });
            }
        }

        return packet;
    }
}
