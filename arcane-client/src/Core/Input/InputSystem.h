#pragma once

#include "Network/Protocol/Packets/ClientInputPacket.h"
#include "Platform/Window.h"

namespace Core::Input
{
    class InputSystem
    {
    public:
        std::optional<Network::ClientInputPacket> PollInput(Platform::Window& window);

    private:
        Network::ClientInputPacket _input{};
    };
}
