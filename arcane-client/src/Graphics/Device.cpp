#include "Graphics/Device.h"

#include "Graphics/GraphicsException.h"
#include "Graphics/Buffer/RenderTarget.h"

namespace Graphics
{
    Device::Device(const HWND hWnd, const int width, const int height)
    {
        CreateDevice();
        CreateSwapChain(hWnd);
        CreateRenderTargets(width, height);
        SetViewport(width, height);
    }

    ID3D11Device* Device::GetDevice() const noexcept
    {
        return _device.Get();
    }

    ID3D11DeviceContext* Device::GetDeviceContext() const noexcept
    {
        return _deviceContext.Get();
    }

    IDXGISwapChain1* Device::GetSwapChain() const noexcept
    {
        return _swapChain.Get();
    }

    std::shared_ptr<Buffer::RenderTarget> Device::GetRenderTarget() const noexcept
    {
        return _renderTarget;
    }

    std::shared_ptr<Buffer::RenderTarget> Device::GetCompositeRenderTarget() const noexcept
    {
        return _compositeRenderTarget;
    }

    void Device::CreateDevice()
    {
#ifdef NDEBUG
        constexpr auto deviceFlags = 0;
#else
        constexpr auto deviceFlags = D3D11_CREATE_DEVICE_DEBUG;
#endif

        SetMarker();
        D3D_FEATURE_LEVEL featureLevel;
        const auto hResult = D3D11CreateDevice(
            nullptr,
            D3D_DRIVER_TYPE_HARDWARE,
            nullptr,
            deviceFlags,
            nullptr, 0,
            D3D11_SDK_VERSION,
            &_device,
            &featureLevel,
            &_deviceContext
        );
        if (FAILED(hResult))
        {
            throw GraphicsException("Failed to create D3D11 device.", hResult, *this);
        }
    }

    void Device::CreateSwapChain(const HWND hWnd)
    {
        SetMarker();
        Microsoft::WRL::ComPtr<IDXGIDevice> dxgiDevice;
        auto hResult = _device.As(&dxgiDevice);
        if (FAILED(hResult))
        {
            throw GraphicsException("Failed to query DXGI device.", hResult, *this);
        }

        SetMarker();
        Microsoft::WRL::ComPtr<IDXGIAdapter> dxgiAdapter;
        hResult = dxgiDevice->GetAdapter(&dxgiAdapter);
        if (FAILED(hResult))
        {
            throw GraphicsException("Failed to get DXGI adapter.", hResult, *this);
        }

        SetMarker();
        Microsoft::WRL::ComPtr<IDXGIFactory2> dxgiFactory;
        hResult = dxgiAdapter->GetParent(IID_PPV_ARGS(&dxgiFactory));
        if (FAILED(hResult))
        {
            throw GraphicsException("Failed to get DXGI factory.", hResult, *this);
        }

        DXGI_SWAP_CHAIN_DESC1 desc;
        desc.Width = 0;
        desc.Height = 0;
        desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        desc.Stereo = FALSE;
        desc.SampleDesc.Count = 1;
        desc.SampleDesc.Quality = 0;
        desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        desc.BufferCount = 2;
        desc.Scaling = DXGI_SCALING_STRETCH;
        desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
        desc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
        desc.Flags = 0;

        SetMarker();
        hResult = dxgiFactory->CreateSwapChainForHwnd(_device.Get(), hWnd, &desc, nullptr, nullptr, &_swapChain);
        if (FAILED(hResult))
        {
            throw GraphicsException("Failed to create swap chain.", hResult, *this);
        }

        SetMarker();
        hResult = dxgiFactory->MakeWindowAssociation(hWnd, DXGI_MWA_NO_ALT_ENTER);
        if (FAILED(hResult))
        {
            throw GraphicsException("Failed to disable ALT+ENTER fullscreen toggle.", hResult, *this);
        }
    }

    void Device::CreateRenderTargets(int width, int height)
    {
        _renderTarget = std::make_shared<Buffer::RenderTarget>(*this, width, height);

        SetMarker();
        Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
        const auto hResult = _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &backBuffer);
        if (FAILED(hResult))
        {
            throw GraphicsException("Failed to get back buffer.", hResult, *this);
        }

        _compositeRenderTarget = std::make_shared<Buffer::RenderTarget>(*this, backBuffer.Get());
    }

    void Device::SetViewport(const int width, const int height) const
    {
        D3D11_VIEWPORT viewport;
        viewport.Width = static_cast<FLOAT>(width);
        viewport.Height = static_cast<FLOAT>(height);
        viewport.MinDepth = 0;
        viewport.MaxDepth = 1;
        viewport.TopLeftX = 0;
        viewport.TopLeftY = 0;

        _deviceContext->RSSetViewports(1, &viewport);
    }

    DXGIDebugQueue& Device::GetInformationManager() noexcept
    {
        return _informationManager;
    }

    void Device::SetMarker()
    {
        _informationManager.SetMarker();
    }
}
