#pragma once

#include "NetworkWorker.h"

namespace Simulation
{
    class ActorSystem;
}

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

        void Update(Simulation::ActorSystem& actorSystem);

        void SendInput(const Core::InputContext& input);

    private:
        NetworkWorker _networkWorker;
    };
}
