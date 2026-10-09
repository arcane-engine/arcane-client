#include "Network/Protocol/ClientPacketBuilder.h"

#include "Network/Protocol/ClientInputPacketBuilder.h"
#include "Network/Protocol/Packets/ClientPacket.h"

namespace Network
{
    ClientPacketBuilder::ClientPacketBuilder(std::uint8_t* buffer, const ClientPacket& packet, const int offset) noexcept
        : _offset(offset)
    {
        _offset = ClientInputPacketBuilder(buffer, packet.Input, _offset).Build();
    }

    int ClientPacketBuilder::Build() const
    {
        return static_cast<std::uint16_t>(_offset + 7) / 8;
    }
}
