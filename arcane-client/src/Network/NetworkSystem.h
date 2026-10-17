#pragma once

#include "NetworkWorker.h"

namespace Simulation
{
    class ActorSystem;
}

namespace Core
{
    struct Context;
}

namespace Network
{
    class NetworkSystem
    {
    public:
        void Start();
        void Stop();

        void Update(Simulation::ActorSystem& actorSystem);

        void Send(const Core::Context& context);

    private:
        NetworkWorker _networkWorker;
    };
}
