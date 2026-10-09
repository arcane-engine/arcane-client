#pragma once

#include <thread>

#include "Network/NetworkClient.h"

namespace Network
{
    class NetworkWorker
    {
    public:
        void Start();
        void Stop();

    private:
        void Send();
        void Receive();

        std::thread _send;
        std::thread _receive;
        std::atomic<bool> _running{ false };
        NetworkClient _client;
    };
}
