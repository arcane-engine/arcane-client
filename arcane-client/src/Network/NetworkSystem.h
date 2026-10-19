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

        void Update(Simulation::ActorSystem& actorSystem, const Core::Context& context);

        void Send(const Core::Context& context);
        void Receive(Simulation::ActorSystem& actorSystem);

    private:
        NetworkWorker _networkWorker;
    };
}
