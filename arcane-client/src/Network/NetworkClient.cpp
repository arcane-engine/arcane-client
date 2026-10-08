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

        auto netSize = size;

        WSABUF buffers[2];
        buffers[0].buf = reinterpret_cast<char*>(&netSize);
        buffers[0].len = sizeof(netSize);

        buffers[1].buf = const_cast<char*>(static_cast<const char*>(data));
        buffers[1].len = size;

        DWORD bytesSent = 0;
        const auto result = WSASend(_socket, buffers, 2, &bytesSent, 0, nullptr, nullptr);

        if (result == SOCKET_ERROR)
        {
            int error = WSAGetLastError();
            Disconnect();
            throw std::runtime_error(std::format("Send failed: {}", error));
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
