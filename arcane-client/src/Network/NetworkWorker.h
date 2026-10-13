#pragma once

#include <thread>

#include "Network/NetworkClient.h"
#include "Network/PacketQueue.h"
#include "Protocol/Packets/ClientPacket.h"
#include "Protocol/Packets/ServerRegisterPacket.h"

namespace Network
{
    class NetworkWorker
    {
    public:
        void Start();
        void Stop();

        void SendQueuePush(const ClientPacket& packet);
        [[nodiscard]] PacketQueue<ServerPacket>& GetReceiveQueue();

    private:
        void Send();
        void Receive();

        std::thread _sendThread;
        std::thread _receiveThread;
        PacketQueue<ClientPacket> _sendQueue;
        PacketQueue<ServerPacket> _receiveQueue;
        std::atomic<bool> _running{ false };
        NetworkClient _networkClient;
    };
}
