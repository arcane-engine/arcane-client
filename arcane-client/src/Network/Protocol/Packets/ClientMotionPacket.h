#pragma once

#include "Math/Vector3.h"

namespace Network
{
    struct ClientMotionPacket
    {
        Math::Vector3 Position;
        Math::Vector3 Velocity;
    };
}
