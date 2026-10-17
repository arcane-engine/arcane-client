#pragma once

#include <vector>

#include "ServerActorPacket.h"

namespace Network
{
    struct ServerPacket
    {
        std::vector<ServerActorPacket> Actor;
        std::vector<ServerActorMotionPacket> ActorMotion;
    };
}
