#pragma once

#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <string>
#include <vector>
#include <cstdint>

namespace Network
{
    class NetworkClient
    {
    public:
        NetworkClient();
        ~NetworkClient();

        NetworkClient(const NetworkClient&) = delete;
        NetworkClient& operator=(const NetworkClient&) = delete;

        [[nodiscard]] bool Connect(const std::string& ip, std::uint16_t port);
        void Disconnect();
        
        [[nodiscard]] bool IsConnected() const;

        [[nodiscard]] bool SendPacket(const void* data, std::size_t size);
        [[nodiscard]] bool ReceivePacket(std::vector<std::uint8_t>& outPayload);

    private:
        bool ReceiveAll(std::uint8_t* buffer, int size) const;

        SOCKET _socket;
        bool _initialized;
        bool _connected;
    };
}
