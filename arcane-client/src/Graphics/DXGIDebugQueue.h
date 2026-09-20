#pragma once

#include <vector>
#include <string>
#include <dxgidebug.h>
#include <wrl.h>

#pragma comment(lib, "dxguid.lib")

namespace Graphics
{
    class DXGIDebugQueue
    {
    public:
        DXGIDebugQueue();
        DXGIDebugQueue(const DXGIDebugQueue&) = delete;
        ~DXGIDebugQueue() = default;

        DXGIDebugQueue& operator=(const DXGIDebugQueue&) = delete;

        void SetMarker() noexcept;
        [[nodiscard]] std::vector<std::string> ReadMessages() const;

    private:
        unsigned long long _next = 0;
        Microsoft::WRL::ComPtr<IDXGIInfoQueue> _queue;
    };
}
