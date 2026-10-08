#pragma once

#include <cstdint>
#include <optional>

#include "Network/Protocol/Packets/ClientInputPacket.h"

namespace Network
{
    class InputPacketBuilder
    {
    public:
        InputPacketBuilder(std::uint8_t* buffer, const std::optional<ClientInputPacket>& packet, int offset) noexcept;

        [[nodiscard]] int Build() const;

    private:
        void SetFlag(std::uint8_t* buffer, int flag, bool value) const noexcept;

        std::optional<ClientInputPacket> _packet;
        int _offset;
    };
}
