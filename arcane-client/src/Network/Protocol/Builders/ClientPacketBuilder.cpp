#include "Network/Protocol/Builders/ClientPacketBuilder.h"

#include "Network/Protocol/Builders/ClientInputPacketBuilder.h"
#include "Network/Protocol/Builders/ClientMotionPacketBuilder.h"
#include "Network/Protocol/Packets/ClientPacket.h"

namespace Network
{
    ClientPacketBuilder::ClientPacketBuilder(std::uint8_t* buffer, const ClientPacket& packet, const int offset) noexcept
        : _offset(offset)
    {
        _offset = ClientInputPacketBuilder(buffer, packet.Input, _offset).Build();
        _offset = ClientMotionPacketBuilder(buffer, packet.Motion, _offset).Build();
    }

    int ClientPacketBuilder::Build() const
    {
        return static_cast<std::uint16_t>(_offset + 7) / 8;
    }
}
