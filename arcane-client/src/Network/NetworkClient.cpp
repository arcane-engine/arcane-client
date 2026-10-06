#include "NetworkClient.h"

#include <iostream>
#include <ws2tcpip.h>
#include <stdexcept>
#include <format>

#pragma comment(lib, "ws2_32.lib")

namespace Network
{
    NetworkClient::NetworkClient()
        : _socket(INVALID_SOCKET), _initialized(false), _connected(false)
    {
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) == 0)
        {
            _initialized = true;
        }
        else
        {
            throw std::runtime_error(std::format("Failed to initialize WinSock: {}", WSAGetLastError()));
        }
    }

    NetworkClient::~NetworkClient()
    {
        Disconnect();
        if (_initialized)
        {
            WSACleanup();
        }
    }

    bool NetworkClient::Connect(const std::string& ip, const uint16_t port)
    {
        if (!_initialized)
        {
            throw std::runtime_error("NetworkClient not initialized.");
        }

        _socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (_socket == INVALID_SOCKET)
        {
            throw std::runtime_error(std::format("Failed to create socket: {}", WSAGetLastError()));
        }

        int flag = 1;
        setsockopt(_socket, IPPROTO_TCP, TCP_NODELAY, reinterpret_cast<char*>(&flag), sizeof(flag));

        sockaddr_in serverAddr{};
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(port);
        inet_pton(AF_INET, ip.c_str(), &serverAddr.sin_addr);

        if (connect(_socket, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR)
        {
            int error = WSAGetLastError();
            closesocket(_socket);
            _socket = INVALID_SOCKET;
            throw std::runtime_error(std::format("Connection failed: {}", error));
        }

        _connected = true;
        return true;
    }

    void NetworkClient::Disconnect()
    {
        if (_socket != INVALID_SOCKET)
        {
            closesocket(_socket);
            _socket = INVALID_SOCKET;
        }
        _connected = false;
    }

    bool NetworkClient::IsConnected() const
    {
        return _connected;
    }

    bool NetworkClient::SendPacket(const void* data, const uint32_t size)
    {
        if (!_connected)
        {
            return false;
        }

        std::vector<char> buffer(4 + size);
        std::memcpy(buffer.data(), &size, 4);
        std::memcpy(buffer.data() + 4, data, size);

        auto totalSent = 0;
        const auto targetSize = static_cast<int>(buffer.size());

        while (totalSent < targetSize)
        {
            const auto sent = send(_socket, buffer.data() + totalSent, targetSize - totalSent, 0);
            if (sent == SOCKET_ERROR)
            {
                int error = WSAGetLastError();
                Disconnect();
                throw std::runtime_error(std::format("Send failed: {}", error));
            }
            totalSent += sent;
        }

        return true;
    }

    bool NetworkClient::ReceivePacket(std::vector<char>& outPayload)
    {
        if (!_connected)
        {
            return false;
        }

        char lengthBuffer[4];
        if (!ReceiveAll(lengthBuffer, 4))
        {
            Disconnect();
            return false;
        }

        const auto payloadSize = *reinterpret_cast<uint32_t*>(lengthBuffer);

        outPayload.resize(payloadSize);
        if (!ReceiveAll(outPayload.data(), static_cast<int>(payloadSize)))
        {
            Disconnect();
            return false;
        }

        return true;
    }

    bool NetworkClient::ReceiveAll(char* buffer, const int size) const
    {
        auto totalBytesRead = 0;

        while (totalBytesRead < size)
        {
            const auto bytesRead = recv(_socket, buffer + totalBytesRead, size - totalBytesRead, 0);
            if (bytesRead <= 0)
            {
                return false;
            }
            totalBytesRead += bytesRead;
        }

        return true;
    }
}
