#pragma once

#include <thread>

#include "NetworkClient.h"

namespace Network
{
    class NetworkWorker
    {
    public:
        void Start();
        void Stop();

    private:
        void Run();

        std::thread _thread;
        std::atomic<bool> _running{ false };
        NetworkClient _client;
    };
}
