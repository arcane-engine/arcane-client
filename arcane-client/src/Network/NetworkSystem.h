#pragma once
#include <optional>

#include "NetworkWorker.h"
#include "Protocol/Packets/ClientInputPacket.h"

namespace Network
{
    class NetworkSystem
    {
    public:
        void Start();
        void Stop();

        void Update();

        void SendInput(std::optional<ClientInputPacket> input);

    private:
        NetworkWorker _networkWorker;
    };
}
