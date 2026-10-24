#pragma once

#include "NetworkWorker.h"

namespace Core { struct Context; }
namespace Scene { class SceneSystem; }
namespace Simulation { class ActorSystem; }

namespace Network
{
    class NetworkSystem
    {
    public:
        void Start();
        void Stop();

        void Update(Simulation::ActorSystem& actorSystem, Scene::SceneSystem& sceneSystem, Core::Context& context);

        void Send(const Core::Context& context);
        void Receive(Simulation::ActorSystem& actorSystem, Scene::SceneSystem& sceneSystem, Core::Context& context);

    private:
        NetworkWorker _networkWorker;
    };
}
