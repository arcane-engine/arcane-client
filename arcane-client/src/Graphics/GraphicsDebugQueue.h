#pragma once

#include <vector>
#include <string>
#include <dxgidebug.h>
#include <wrl/client.h>

#pragma comment(lib, "dxguid.lib")

namespace Graphics
{
    class GraphicsDebugQueue
    {
    public:
        GraphicsDebugQueue();
        GraphicsDebugQueue(const GraphicsDebugQueue&) = delete;
        ~GraphicsDebugQueue() = default;

        GraphicsDebugQueue& operator=(const GraphicsDebugQueue&) = delete;

        void SetMarker() noexcept;
        [[nodiscard]] std::vector<std::string> ReadMessages() const;

    private:
        unsigned long long _next = 0;
        Microsoft::WRL::ComPtr<IDXGIInfoQueue> _queue;
    };
}
