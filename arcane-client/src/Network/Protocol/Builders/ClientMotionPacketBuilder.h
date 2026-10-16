#pragma once

#include <cstdint>
#include <optional>

#include "Network/Protocol/Packets/ClientMotionPacket.h"

namespace Network
{
    class ClientMotionPacketBuilder
    {
    public:
        ClientMotionPacketBuilder(std::uint8_t* buffer, const std::optional<ClientMotionPacket>& packet, int offset) noexcept;

        [[nodiscard]] int Build() const;

    private:
        void WriteBit(std::uint8_t* buffer, bool value) noexcept;
        void WriteBits(std::uint8_t* buffer, std::uint32_t value, int bits) noexcept;
        void WriteFloat(std::uint8_t* buffer, float value) noexcept;

        std::optional<ClientMotionPacket> _packet;
        int _offset;
    };
}
