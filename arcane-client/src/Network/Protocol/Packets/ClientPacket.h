#pragma once

#include <optional>

#include "Network/Protocol/Packets/ClientInputPacket.h"

namespace Network
{
    struct ClientInputPacket;

    struct ClientPacket
    {
        std::optional<ClientInputPacket> Input;
    };
}
