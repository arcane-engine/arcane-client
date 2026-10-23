#include "NetworkSystem.h"

#include "Core/Context/Context.h"
#include "Core/Context/InputContext.h"
#include "Protocol/Packets/ClientPacket.h"
#include "Protocol/Packets/ServerPacket.h"
#include "Scene/SceneSystem.h"
#include "Simulation/ActorSystem.h"

namespace Network
{
    void NetworkSystem::Start()
    {
        _networkWorker.Start();
    }

    void NetworkSystem::Stop()
    {
        _networkWorker.Stop();
    }

    void NetworkSystem::Update(Simulation::ActorSystem& actorSystem, Scene::SceneSystem& sceneSystem, const Core::Context& context)
    {
        Send(context);
        Receive(actorSystem, sceneSystem);
    }

    void NetworkSystem::Send(const Core::Context& context)
    {
        if (context.Input.Keyboard.Changed)
        {
            _networkWorker.SendQueuePush(ClientPacket{
                .Input = ClientInputPacket{
                    .Forward = context.Input.Keyboard.Forward,
                    .Backward = context.Input.Keyboard.Backward,
                    .Left = context.Input.Keyboard.Left,
                    .Right = context.Input.Keyboard.Right
                },
                .Motion = ClientMotionPacket{
                    .Position = context.Camera.Target,
                    .Velocity = context.Camera.Velocity
                }
            });
        }
    }

    void NetworkSystem::Receive(Simulation::ActorSystem& actorSystem, Scene::SceneSystem& sceneSystem)
    {
        std::queue<ServerPacket> queue;
        _networkWorker.GetReceiveQueue().Swap(queue);

        while (queue.empty() == false)
        {
            const auto& packet = queue.front();

            if (packet.Actor.empty() == false)
            {
                for (const auto& actor : packet.Actor)
                {
                    if (actor.Register)
                    {
                        actorSystem.CreateActor(actor.Id, Math::Vector3(0, 0, 0), Math::Quaternion(0, 0, 0, 0), Math::Vector3(1, 1, 1));
                    }
                    else
                    {
                        actorSystem.RemoveActor(actor.Id);
                    }
                }
            }
            if (packet.ActorMotion.empty() == false)
            {
                for (const auto& actorMotion : packet.ActorMotion)
                {
                    actorSystem.GetActor(actorMotion.Id)->SetPosition(actorMotion.Position);
                    actorSystem.GetActor(actorMotion.Id)->SetVelocity(actorMotion.Velocity);
                }
            }
            if (packet.SceneNodes.empty() == false)
            {
                for (auto sceneNode : packet.SceneNodes)
                {
                    auto node = Scene::SceneNode();
                    node.SetSceneObject(sceneSystem.GetSceneObject(sceneNode.Mesh, sceneNode.Material));
                    node.SetPosition(sceneNode.Position);
                    node.SetRotation(sceneNode.Rotation);
                    node.SetScale(sceneNode.Scale);
                    sceneSystem.AddSceneNode(std::move(node));
                }
            }

            queue.pop();
        }
    }
}
