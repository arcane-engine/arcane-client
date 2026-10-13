#pragma once

#include <mutex>
#include <queue>

namespace Network
{
    template<typename T>
    class PacketQueue
    {
    public:
        void Push(T&& packet);
        void Push(const T& packet);
        void Swap(std::queue<T>& targetQueue);

    private:
        mutable std::mutex _mutex;
        std::queue<T> _queue;
    };
}

#include "Network/PacketQueue.inl"