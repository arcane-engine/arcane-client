#pragma once

#include "Network/PacketQueue.h"

namespace Network
{
    template<typename T>
    void PacketQueue<T>::Push(T&& packet)
    {
        std::lock_guard lock(_mutex);
        _queue.push(std::move(packet));
    }

    template<typename T>
    void PacketQueue<T>::Push(const T& packet)
    {
        std::lock_guard lock(_mutex);
        _queue.push(packet);
    }

    template<typename T>
    void PacketQueue<T>::Swap(std::queue<T>& targetQueue)
    {
        std::lock_guard lock(_mutex);
        targetQueue.swap(_queue);
    }
}
