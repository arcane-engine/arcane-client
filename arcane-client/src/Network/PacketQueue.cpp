#include "Network/PacketQueue.h"

namespace Network
{
    void PacketQueue::Push(std::vector<uint8_t>&& packet)
    {
        std::scoped_lock lock(_mutex);
        _queue.push(std::move(packet));
    }

    void PacketQueue::Swap(std::queue<std::vector<uint8_t>>& targetQueue)
    {
        std::scoped_lock lock(_mutex);
        if (_queue.empty())
        {
            return;
        }

        targetQueue.swap(_queue);
    }
}
