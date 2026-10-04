#pragma once

#include <vector>
#include <string>
#include <wrl/client.h>

#pragma comment(lib, "dxguid.lib")

struct IDXGIInfoQueue;

namespace Graphics
{
    class GraphicsDebugQueue
    {
    public:
        GraphicsDebugQueue();
        GraphicsDebugQueue(const GraphicsDebugQueue&) = delete;
        ~GraphicsDebugQueue();

        GraphicsDebugQueue& operator=(const GraphicsDebugQueue&) = delete;

        void SetMarker() noexcept;
        [[nodiscard]] std::vector<std::string> ReadMessages() const;

    private:
        unsigned long long _next = 0;
        Microsoft::WRL::ComPtr<IDXGIInfoQueue> _queue;
    };
}
