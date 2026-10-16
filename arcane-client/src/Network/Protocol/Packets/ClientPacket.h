#pragma once

#include <optional>

#include "Network/Protocol/Packets/ClientInputPacket.h"
#include "Network/Protocol/Packets/ClientMotionPacket.h"

namespace Network
{
    struct ClientPacket
    {
        std::optional<ClientInputPacket> Input;
        std::optional<ClientMotionPacket> Motion;
    };
}
