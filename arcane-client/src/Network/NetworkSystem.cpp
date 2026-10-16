#include "NetworkSystem.h"

#include "Core/Context/InputContext.h"
#include "Protocol/Packets/ClientPacket.h"
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

    void NetworkSystem::Update(Simulation::ActorSystem& actorSystem)
    {
        std::queue<ServerPacket> queue;
        _networkWorker.GetReceiveQueue().Swap(queue);

        while (!queue.empty())
        {
            const auto& packet = queue.front();

            if (!packet.Actor.empty())
            {
                const auto& reg = packet.Actor[0];
                if (reg.Register)
                {
                    actorSystem.CreateActor(reg.Id, Math::Vector3(5, 1, 5), Math::Quaternion(0, 0, 0, 0), Math::Vector3(1, 1, 1));
                }
                else
                {
                    actorSystem.RemoveActor(reg.Id);
                }
            }

            queue.pop();
        }
    }

    void NetworkSystem::SendInput(const Core::InputContext& input)
    {
        if (input.Keyboard.Changed)
        {
            _networkWorker.SendQueuePush(ClientPacket{
                .Input = ClientInputPacket{
                    .Forward = input.Keyboard.Forward,
                    .Backward = input.Keyboard.Backward,
                    .Left = input.Keyboard.Left,
                    .Right = input.Keyboard.Right
                },
                .Motion = ClientMotionPacket{
                    .Position = { 1, 2, 3 },
                    .Velocity = { 4, 5, 6 }
                }
            });
        }
    }
}
