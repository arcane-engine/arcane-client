#pragma once

#include <cstdint>

namespace Network
{
    struct ClientPacket;

    class PacketBuilder
    {
    public:
        explicit PacketBuilder(std::uint8_t* buffer, const ClientPacket& packet, int offset = 0) noexcept;

        [[nodiscard]] int Build() const;

    private:
        int _offset;
    };
}
