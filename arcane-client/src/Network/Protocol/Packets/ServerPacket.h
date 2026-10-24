#pragma once

#include <optional>
#include <vector>

#include "ServerActorPacket.h"

namespace Network
{
    struct ServerPacket
    {
        std::optional<ServerActorSetupPacket> ActorSetup;
        std::vector<ServerActorRegisterPacket> ActorRegister;
        std::vector<ServerActorMotionPacket> ActorMotion;
        std::vector<ServerSceneNodePacket> SceneNodes;
    };
}
