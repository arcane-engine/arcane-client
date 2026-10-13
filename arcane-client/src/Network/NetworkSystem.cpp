#include "NetworkSystem.h"

#include "Core/Context/InputContext.h"
#include "Protocol/Packets/ClientPacket.h"

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

    void NetworkSystem::Update()
    {
        std::queue<ServerPacket> queue;
        _networkWorker.GetReceiveQueue().Swap(queue);

        while (!queue.empty())
        {
            const auto& packet = queue.front();

            if (!packet.Register.empty())
            {
                const auto& reg = packet.Register[0];
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
                }
            });
        }
    }
}
