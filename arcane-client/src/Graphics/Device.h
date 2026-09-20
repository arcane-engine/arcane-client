#pragma once

#include <d3d11.h>
#include <dxgi1_2.h>
#include <memory>
#include <wrl.h>

#include "Graphics/DXGIDebugQueue.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

namespace Graphics::Buffer
{
    class RenderTarget;
}

namespace Graphics
{
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
        [[nodiscard]] std::shared_ptr<Buffer::RenderTarget> GetRenderTarget() const noexcept;
        [[nodiscard]] std::shared_ptr<Buffer::RenderTarget> GetCompositeRenderTarget() const noexcept;

    private:
        void CreateDevice();
        void CreateSwapChain(HWND hWnd);
        void CreateRenderTargets(int width, int height);
        void SetViewport(int width, int height) const;

        DXGIDebugQueue& GetInformationManager() noexcept;

    private:
        Microsoft::WRL::ComPtr<ID3D11Device> _device;
        Microsoft::WRL::ComPtr<IDXGISwapChain1> _swapChain;
        Microsoft::WRL::ComPtr<ID3D11DeviceContext> _deviceContext;
        std::shared_ptr<Buffer::RenderTarget> _renderTarget;
        std::shared_ptr<Buffer::RenderTarget> _compositeRenderTarget;
        DXGIDebugQueue _informationManager;
    };
}
