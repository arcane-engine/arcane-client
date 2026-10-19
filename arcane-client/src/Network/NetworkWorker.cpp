#include "Network/NetworkWorker.h"

#include "Core/Common/Exception.h"
#include "Network/Protocol/Builders/ClientPacketBuilder.h"
#include "Network/Protocol/Packets/ClientPacket.h"
#include "Protocol/ServerPacketReader.h"

namespace Network
{
    void NetworkWorker::Start()
    {
        _running = true;

        if (!_networkClient.Connect("127.0.0.1", 5000))
        {
            throw Core::Exception("Failed to connect to server.");
        }

        _sendThread = std::thread(&NetworkWorker::Send, this);
        _receiveThread = std::thread(&NetworkWorker::Receive, this);
    }

    void NetworkWorker::Stop()
    {
        _running = false;

        _networkClient.Disconnect();
        if (_sendThread.joinable())
        {
            _sendThread.join();
        }
        if (_receiveThread.joinable())
        {
            _receiveThread.join();
        }
    }

    void NetworkWorker::SendQueuePush(const ClientPacket& packet)
    {
        return _sendQueue.Push(packet);
    }

    PacketQueue<ServerPacket>& NetworkWorker::GetReceiveQueue()
    {
        return _receiveQueue;
    }

    void NetworkWorker::Send()
    {
        constexpr std::chrono::microseconds sleep(1000000 / 60);

        while (_running)
        {
            auto startTime = std::chrono::steady_clock::now();

            std::queue<ClientPacket> queue;
            _sendQueue.Swap(queue);

            while (!queue.empty())
            {
                std::uint8_t buffer[8192]{};
                const auto size = ClientPacketBuilder(buffer, queue.front()).Build();
                _networkClient.SendPacket(buffer, size);
                queue.pop();
            }

            auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - startTime);

            if (elapsed < sleep)
            {
                std::this_thread::sleep_for(sleep - elapsed);
            }
        }
    }

    void NetworkWorker::Receive()
    {
        constexpr std::chrono::microseconds sleep(1000000 / 60);

        while (_running)
        {
            auto startTime = std::chrono::steady_clock::now();

            std::vector<std::uint8_t> buffer;
            while (_networkClient.ReceivePacket(buffer))
            {
                auto packet = ServerPacketReader::Read(buffer.data());
                _receiveQueue.Push(std::move(packet));
                buffer.clear();
            }

            auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - startTime);

            if (elapsed < sleep)
            {
                std::this_thread::sleep_for(sleep - elapsed);
            }
        }
    }
}
