#include "Network/Protocol/Builders/ClientMotionPacketBuilder.h"

#include <bit>

namespace Network
{
    ClientMotionPacketBuilder::ClientMotionPacketBuilder(std::uint8_t* buffer, const std::optional<ClientMotionPacket>& packet, const int offset) noexcept
        : _packet(packet), _offset(offset)
    {
        WriteBit(buffer, packet.has_value());
        if (_packet)
        {
            const auto value = packet.value();
            WriteFloat(buffer, value.Position.X);
            WriteFloat(buffer, value.Position.Y);
            WriteFloat(buffer, value.Position.Z);
            WriteFloat(buffer, value.Velocity.X);
            WriteFloat(buffer, value.Velocity.Y);
            WriteFloat(buffer, value.Velocity.Z);
        }
    }

    int ClientMotionPacketBuilder::Build() const
    {
        return _offset;
    }

    void ClientMotionPacketBuilder::WriteBit(std::uint8_t* buffer, const bool value) noexcept
    {
        if (value)
        {
            const auto byte = _offset / 8;
            const auto bit = 7 - _offset % 8;
            buffer[byte] |= 1u << bit;
        }
        _offset++;
    }

    void ClientMotionPacketBuilder::WriteBits(std::uint8_t* buffer, const std::uint32_t value, const int bits) noexcept
    {
        for (int i = bits - 1; i >= 0; --i)
        {
            if ((value & (1u << i)) != 0)
            {
                const auto byte = _offset / 8;
                const auto bit = 7 - (_offset % 8);
                buffer[byte] |= (1u << bit);
            }
            _offset++;
        }
    }

    void ClientMotionPacketBuilder::WriteFloat(std::uint8_t* buffer, const float value) noexcept
    {
        const auto bits = std::bit_cast<std::uint32_t>(value);
        WriteBits(buffer, bits, 32);
    }
}
