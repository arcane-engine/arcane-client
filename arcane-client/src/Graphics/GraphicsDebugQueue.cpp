#include "Graphics/GraphicsDebugQueue.h"

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
    GraphicsDebugQueue::GraphicsDebugQueue()
    {}

    void GraphicsDebugQueue::Mark() noexcept
    {}

    std::vector<std::string> GraphicsDebugQueue::GetMessages() const
    {
        return {};
    }
#else
    GraphicsDebugQueue::GraphicsDebugQueue()
    {
        typedef HRESULT(WINAPI* GetDebugInterface)(REFIID, void**);

        const auto hModDxgiDebug = LoadLibraryEx(L"dxgidebug.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
        if (hModDxgiDebug == nullptr)
        {
            throw Core::Platform::WindowException("Failed to load 'dxgidebug.dll' system library.", GetLastError());
        }

        const auto rawProc = reinterpret_cast<void*>(GetProcAddress(hModDxgiDebug, "DXGIGetDebugInterface"));
        const auto getDebugInterface = reinterpret_cast<GetDebugInterface>(rawProc);
        if (getDebugInterface == nullptr)
        {
            throw Core::Platform::WindowException("Failed to locate 'DXGIGetDebugInterface' export in 'dxgidebug.dll'.", GetLastError());
        }

        const auto hResult = getDebugInterface(IID_PPV_ARGS(&_queue));
        if (FAILED(hResult))
        {
            throw GraphicsException("Failed to create DXGI debug info queue interface.", hResult);
        }
    }

    GraphicsDebugQueue::~GraphicsDebugQueue() = default;

    void GraphicsDebugQueue::SetMarker() noexcept
    {
        _next = _queue->GetNumStoredMessages(DXGI_DEBUG_ALL);
    }

    std::vector<std::string> GraphicsDebugQueue::ReadMessages() const
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
