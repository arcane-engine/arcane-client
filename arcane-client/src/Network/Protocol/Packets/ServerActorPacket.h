#pragma once

#include <string>

#include "Math/Quaternion.h"
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

    struct ServerSceneNodePacket
    {
        std::uint16_t Id;
        std::string Mesh;
        std::string Material;
        Math::Vector3 Position;
        Math::Quaternion Rotation;
        Math::Vector3 Scale;
    };
}
