#include "Network/NetworkWorker.h"

#include "Core/Common/Exception.h"
#include "Network/Protocol/ClientPacketBuilder.h"
#include "Network/Protocol/Packets/ClientPacket.h"

namespace Network
{
    void NetworkWorker::Start()
    {
        _running = true;

        if (!_client.Connect("127.0.0.1", 5000))
        {
            throw Core::Exception("Failed to connect to server.");
        }

        _send = std::thread(&NetworkWorker::Send, this);
        _receive = std::thread(&NetworkWorker::Receive, this);
    }

    void NetworkWorker::Stop()
    {
        _running = false;
        _client.Disconnect();
        if (_send.joinable())
        {
            _send.join();
        }
        if (_receive.joinable())
        {
            _receive.join();
        }
    }

    void NetworkWorker::Send()
    {
        constexpr std::chrono::microseconds sleep(1000000 / 60);

        while (_running)
        {
            auto startTime = std::chrono::steady_clock::now();

            std::queue<std::vector<std::uint8_t>> queue;
            _sendQueue.Swap(queue);

            while (!queue.empty())
            {
                const auto& data = queue.front();

                auto _ = _client.SendPacket(data.data(), data.size());

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

            std::vector<std::uint8_t> packet;
            while (_client.ReceivePacket(packet))
            {
                _receiveQueue.Push(std::move(packet));

                packet = std::vector<std::uint8_t>();
            }

            auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - startTime);

            if (elapsed < sleep)
            {
                std::this_thread::sleep_for(sleep - elapsed);
            }
        }
    }
}
