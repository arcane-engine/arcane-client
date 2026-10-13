#pragma once

#include "NetworkWorker.h"

namespace Core
{
    struct InputContext;
}

namespace Network
{
    class NetworkSystem
    {
    public:
        void Start();
        void Stop();

        void Update();

        void SendInput(const Core::InputContext& input);

    private:
        NetworkWorker _networkWorker;
    };
}
