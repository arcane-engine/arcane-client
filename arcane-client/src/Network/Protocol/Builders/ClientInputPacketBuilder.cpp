#include "Network/Protocol/Builders/ClientInputPacketBuilder.h"

namespace Network
{
    ClientInputPacketBuilder::ClientInputPacketBuilder(std::uint8_t* buffer, const std::optional<ClientInputPacket>& packet, const int offset) noexcept
        : _packet(packet), _offset(offset)
    {
        WriteBit(buffer, _packet.has_value());
        if (_packet)
        {
            const auto value = _packet.value();
            WriteBit(buffer, value.Forward);
            WriteBit(buffer, value.Backward);
            WriteBit(buffer, value.Left);
            WriteBit(buffer, value.Right);
        }
    }

    int ClientInputPacketBuilder::Build() const
    {
        return _offset;
    }

    void ClientInputPacketBuilder::WriteBit(std::uint8_t* buffer, const bool value) noexcept
    {
        if (value)
        {
            const auto byte = _offset / 8;
            const auto bit = 7 - _offset % 8;
            buffer[byte] |= 1u << bit;
        }
        _offset++;
    }
}
