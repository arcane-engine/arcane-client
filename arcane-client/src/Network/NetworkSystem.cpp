#include "NetworkSystem.h"

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
                const auto& reg = packet.Register[0]; // funkar... breakpoint här biter som tänkt...
            }

            queue.pop();
        }
    }

    void NetworkSystem::SendInput(const std::optional<ClientInputPacket> input)
    {
        if (input)
        {
            _networkWorker.SendQueuePush(ClientPacket{ .Input = input });
        }
    }
}
