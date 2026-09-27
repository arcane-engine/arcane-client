#pragma once

#include <d3d11.h>
#include <dxgi1_2.h>
#include <memory>
#include <wrl/client.h>

#include "Graphics/DXGIDebugQueue.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

namespace Graphics
{
    class DepthStencil;
    class RenderTarget;
    class GraphicsException;

    class Device
    {
        friend GraphicsException;

    public:
        Device(HWND hWnd, int width, int height);

        ~Device() = default;

        Device(const Device&) = delete;
        Device(Device&&) = delete;

        Device& operator=(const Device&) = delete;
        Device& operator=(Device&& device) = delete;

        void SetMarker();

        [[nodiscard]] ID3D11Device* GetDevice() const noexcept;
        [[nodiscard]] ID3D11DeviceContext* GetDeviceContext() const noexcept;
        [[nodiscard]] IDXGISwapChain1* GetSwapChain() const noexcept;
        [[nodiscard]] std::shared_ptr<RenderTarget> GetSceneRenderTarget() const noexcept;
        [[nodiscard]] std::shared_ptr<RenderTarget> GetOutputRenderTarget() const noexcept;
        [[nodiscard]] std::shared_ptr<DepthStencil> GetDepthStencil() const noexcept;

    private:
        void CreateDevice();
        void CreateSwapChain(HWND hWnd);
        void CreateRenderTargets(int width, int height);
        void SetViewport(int width, int height) const;

        DXGIDebugQueue& GetDebugQueue() noexcept;

    private:
        Microsoft::WRL::ComPtr<ID3D11Device> _device;
        Microsoft::WRL::ComPtr<IDXGISwapChain1> _swapChain;
        Microsoft::WRL::ComPtr<ID3D11DeviceContext> _deviceContext;
        std::shared_ptr<RenderTarget> _sceneRenderTarget;
        std::shared_ptr<RenderTarget> _outputRenderTarget;
        std::shared_ptr<DepthStencil> _depthStencil;
        DXGIDebugQueue _debugQueue;
    };
}
