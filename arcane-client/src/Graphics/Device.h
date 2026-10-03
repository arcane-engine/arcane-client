#pragma once

#include <d3d11.h>
#include <dxgi1_2.h>
#include <memory>
#include <wrl/client.h>

#include "Graphics/DeviceContextCache.h"
#include "Graphics/GraphicsDebugQueue.h"
#include "RenderTarget/DepthStencil.h"

namespace Graphics
{
    class DepthStencil;
    class RenderTarget;
    class GraphicsException;

    class Device
    {
    public:
        Device(HWND hWnd, int width, int height);

        ~Device() = default;

        Device(const Device&) = delete;
        Device(Device&&) = delete;

        Device& operator=(const Device&) = delete;
        Device& operator=(Device&& device) = delete;

        [[nodiscard]] ID3D11Device* GetDevice() const noexcept;
        [[nodiscard]] ID3D11DeviceContext* GetDeviceContext() const noexcept;
        [[nodiscard]] IDXGISwapChain1* GetSwapChain() const noexcept;
        [[nodiscard]] std::shared_ptr<RenderTarget> GetGeometryRenderTarget() const noexcept;
        [[nodiscard]] std::shared_ptr<RenderTarget> GetCompositeRenderTarget() const noexcept;
        [[nodiscard]] std::shared_ptr<DepthStencil> GetDepthStencil() const noexcept;
        [[nodiscard]] DeviceContextCache& GetContextCache() noexcept;
        [[nodiscard]] std::vector<std::string> GetDebugMessages() const noexcept;

        void SetResolution(int width, int height);

        void SetMarker();

    private:
        void CreateDevice();
        void CreateSwapChain(HWND hWnd);
        void CreateRenderTargets(int width, int height);
        void SetViewport(int width, int height) const;

    private:
        Microsoft::WRL::ComPtr<ID3D11Device> _device;
        Microsoft::WRL::ComPtr<IDXGISwapChain1> _swapChain;
        Microsoft::WRL::ComPtr<ID3D11DeviceContext> _deviceContext;
        std::shared_ptr<RenderTarget> _geometryRenderTarget;
        std::shared_ptr<RenderTarget> _compositeRenderTarget;
        std::shared_ptr<DepthStencil> _depthStencil;
        DeviceContextCache _contextCache;
        mutable GraphicsDebugQueue _debugQueue;
    };
}
