#include "Network/Protocol/PacketBuilder.h"

#include "Network/Protocol/InputPacketBuilder.h"
#include "Network/Protocol/Packets/ClientPacket.h"

namespace Network
{
    PacketBuilder::PacketBuilder(std::uint8_t* buffer, const ClientPacket& packet, const int offset) noexcept
        : _offset(offset)
    {
        _offset = InputPacketBuilder(buffer, packet.Input, _offset).Build();
    }

    int PacketBuilder::Build() const
    {
        return static_cast<std::uint16_t>(_offset + 7) / 8;
    }
}
