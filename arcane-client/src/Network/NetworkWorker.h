#pragma once

#include <thread>

#include "PacketQueue.h"
#include "Network/NetworkClient.h"

namespace Network
{
    class NetworkWorker
    {
    public:
        void Start();
        void Stop();

        [[nodiscard]] PacketQueue& GetSendQueue() { return _sendQueue; }
        [[nodiscard]] PacketQueue& GetReceiveQueue() { return _receiveQueue; }

    private:
        void Send();
        void Receive();

        std::thread _send;
        std::thread _receive;
        PacketQueue _sendQueue;
        PacketQueue _receiveQueue;
        std::atomic<bool> _running{ false };
        NetworkClient _client;
    };
}
