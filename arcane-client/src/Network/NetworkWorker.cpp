#include "Network/NetworkWorker.h"

#include "Core/Common/Exception.h"
#include "Network/Protocol/PacketBuilder.h"
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

            uint8_t buffer[256]{};
            auto packet = ClientPacket();
            packet.Input = ClientInputPacket();
            packet.Input->Forward = true;
            packet.Input->Backward = true;
            packet.Input->Left = false;
            packet.Input->Right = false;
            const auto size = PacketBuilder(buffer, packet).Build();

            auto _ = _client.SendPacket(buffer, size);

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

            std::vector<uint8_t> buffer;

            if (!_client.ReceivePacket(buffer))
            {
                break;
            }

            auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - startTime);

            if (elapsed < sleep)
            {
                std::this_thread::sleep_for(sleep - elapsed);
            }
        }
    }
}
