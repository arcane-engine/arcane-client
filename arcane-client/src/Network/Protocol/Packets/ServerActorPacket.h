#pragma once

#include "Math/Vector3.h"

namespace Network
{
    struct ServerActorPacket
    {
        std::uint16_t Id;
        bool Register;
    };

    struct ServerActorMotionPacket
    {
        std::uint16_t Id;
        Math::Vector3 Position;
        Math::Vector3 Velocity;
    };
}
