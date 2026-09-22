#include "Graphics/DXGIDebugQueue.h"

#include <dxgidebug.h>
#include <format>
#include <memory>

#include "Core/Platform/Window.h"
#include "Core/Platform/WindowException.h"
#include "Graphics/GraphicsException.h"

#pragma comment(lib, "dxguid.lib")

namespace Graphics
{
#ifdef NDEBUG
    DXGIDebugQueue::DXGIDebugQueue()
    {}

    void DXGIDebugQueue::Mark() noexcept
    {}

    std::vector<std::string> DXGIDebugQueue::GetMessages() const
    {
        return {};
    }
#else
    DXGIDebugQueue::DXGIDebugQueue()
    {
        typedef HRESULT(WINAPI* DXGIGetDebugInterface)(REFIID, void**);

        const auto hModDxgiDebug = LoadLibraryEx(L"dxgidebug.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
        if (hModDxgiDebug == nullptr)
        {
            throw Core::Platform::WindowException("Failed to load 'dxgidebug.dll' system library.", GetLastError());
        }

        const auto dxgiGetDebugInterface = reinterpret_cast<DXGIGetDebugInterface>(reinterpret_cast<void*>(GetProcAddress(hModDxgiDebug, "DXGIGetDebugInterface")));
        if (dxgiGetDebugInterface == nullptr)
        {
            throw Core::Platform::WindowException("Failed to locate 'DXGIGetDebugInterface' export in 'dxgidebug.dll'.", GetLastError());
        }

        const auto hResult = dxgiGetDebugInterface(__uuidof(IDXGIInfoQueue), &_queue);
        if (FAILED(hResult))
        {
            throw GraphicsException("Failed to create DXGI debug info queue interface.", hResult);
        }
    }

    void DXGIDebugQueue::SetMarker() noexcept
    {
        _next = _queue->GetNumStoredMessages(DXGI_DEBUG_ALL);
    }

    std::vector<std::string> DXGIDebugQueue::ReadMessages() const
    {
        std::vector<std::string> messages;
        const auto end = _queue->GetNumStoredMessages(DXGI_DEBUG_ALL);
        for (auto i = _next; i < end; i++)
        {
            SIZE_T length;

            auto hResult = _queue->GetMessage(DXGI_DEBUG_ALL, i, nullptr, &length);
            if (FAILED(hResult))
            {
                throw GraphicsException(std::format("Failed to get DXGI debug message length at index {}.", i), hResult);
            }

            auto bytes = std::make_unique<byte[]>(length);
            const auto message = reinterpret_cast<DXGI_INFO_QUEUE_MESSAGE*>(bytes.get());

            hResult = _queue->GetMessage(DXGI_DEBUG_ALL, i, message, &length);
            if (FAILED(hResult))
            {
                throw GraphicsException(std::format("Failed to retrieve DXGI debug message content at index {}.", i), hResult);
            }

            messages.emplace_back(message->pDescription);
        }

        return messages;
    }
#endif
}
