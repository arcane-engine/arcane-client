#pragma once

#include "Math/Vector3.h"

namespace Network
{
    struct ClientMotionPacket
    {
        std::optional<Math::Vector3> Direction;
    };
}
