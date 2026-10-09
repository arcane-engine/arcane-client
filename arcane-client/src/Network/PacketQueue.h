#pragma once

#include <mutex>
#include <queue>

namespace Network
{
    class PacketQueue
    {
    public:
        void Push(std::vector<std::uint8_t>&& packet);
        void Swap(std::queue<std::vector<std::uint8_t>>& targetQueue);

    private:
        std::mutex _mutex;
        std::queue<std::vector<std::uint8_t>> _queue;
    };
}
