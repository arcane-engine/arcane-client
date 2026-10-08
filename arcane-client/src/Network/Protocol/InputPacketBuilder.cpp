#include "Network/Protocol/InputPacketBuilder.h"

namespace Network
{
    namespace
    {
        constexpr int Size = 8;

        constexpr int Include  = Size - 1;
        constexpr int Forward  = Size - 2;
        constexpr int Backward = Size - 3;
        constexpr int Left     = Size - 4;
        constexpr int Right    = Size - 5;
    }

    InputPacketBuilder::InputPacketBuilder(std::uint8_t* buffer, const std::optional<ClientInputPacket>& packet, const int offset) noexcept
        : _packet(packet), _offset(offset)
    {
        if (_packet)
        {
            SetFlag(buffer, Include, true);
            SetFlag(buffer, Forward, _packet->Forward);
            SetFlag(buffer, Backward, _packet->Backward);
            SetFlag(buffer, Left, _packet->Left);
            SetFlag(buffer, Right, _packet->Right);
        }
    }

    int InputPacketBuilder::Build() const
    {
        return _packet ? _offset + Size : _offset + 1;
    }

    void InputPacketBuilder::SetFlag(std::uint8_t* buffer, const int flag, const bool value) const noexcept
    {
        if (value)
        {
            const auto byte = _offset / Size;
            const auto bit = _offset % Size;
            buffer[byte] |= 1u << (flag + bit);
        }
    }
}
