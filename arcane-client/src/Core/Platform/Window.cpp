#include "Core/Platform/Window.h"

#include <bit>

#include "Core/Platform/WindowException.h"

namespace Core::Platform
{
    Window::Window(const int width, const int height) :
        _windowClass(HandleMessageSetup),
        _mouse(width, height)
    {
        const auto wr = GetWindowRect(width, height);

        _hWnd = CreateWindow(
            _windowClass.GetName(),
            L"Client",
            _windowStyle,
            200,
            200,
            wr.right - wr.left,
            wr.bottom - wr.top,
            nullptr,
            nullptr,
            _windowClass.GetInstance(),
            this
        );

        if (_hWnd == nullptr)
        {
            throw WindowException("Create window failed.", GetLastError());
        }

        RegisterRawMouseInputDevice();

        ShowWindow(_hWnd, SW_SHOWDEFAULT);

        CaptureMouseCursor(width, height);
    }

    Window::~Window()
    {
        DestroyWindow(_hWnd);
    }

    void Window::RegisterRawMouseInputDevice()
    {
        RAWINPUTDEVICE device;
        device.usUsagePage = 0x01;
        device.usUsage = 0x02;
        device.dwFlags = 0;
        device.hwndTarget = nullptr;

        if (RegisterRawInputDevices(&device, 1, sizeof(device)) == false)
        {
            throw Exception("Unable to register raw mouse input.");
        }
    }

    void Window::CaptureMouseCursor(const int width, const int height)
    {
        const RECT rect = { .left = 0, .top = 0, .right = width, .bottom = height };
        ClipCursor(&rect);
        ShowCursor(false);
    }

    LRESULT CALLBACK Window::HandleMessageSetup(const HWND hWnd, const UINT msg, const WPARAM wParam, const LPARAM lParam)
    {
        if (msg == WM_NCCREATE)
        {
            const auto* create = std::bit_cast<CREATESTRUCT*>(lParam);
            auto* window = static_cast<Window*>(create->lpCreateParams);

            SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
            SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMessageProxy));

            return window->HandleMessage(hWnd, msg, wParam, lParam);
        }

        return DefWindowProc(hWnd, msg, wParam, lParam);
    }

    LRESULT CALLBACK Window::HandleMessageProxy(const HWND hWnd, const UINT msg, const WPARAM wParam, const LPARAM lParam)
    {
        auto* window = std::bit_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

        if (window != nullptr)
        {
            return window->HandleMessage(hWnd, msg, wParam, lParam);
        }

        return DefWindowProc(hWnd, msg, wParam, lParam);
    }

    LRESULT Window::HandleMessage(const HWND hWnd, const UINT msg, const WPARAM wParam, const LPARAM lParam)
    {
        HandleSystemMessage(msg);
        HandleKeyboardMessage(msg, wParam, lParam);
        HandleRawInputMessage(lParam);
        HandleMouseMessage(msg, wParam, lParam);

        if (msg == WM_CLOSE)
        {
            return 0;
        }

        return DefWindowProc(hWnd, msg, wParam, lParam);
    }

    void Window::HandleSystemMessage(const UINT msg) noexcept
    {
        if (msg == WM_CLOSE)
        {
            PostQuitMessage(0);
        }
    }

    void Window::HandleKeyboardMessage(const UINT msg, const WPARAM wParam, const LPARAM lParam)
    {
        if (msg == WM_KILLFOCUS)
        {
            _keyboard.ClearState();
        }
        else if (msg == WM_KEYDOWN || msg == WM_SYSKEYDOWN)
        {
            if (IsAutoRepeat(lParam))
            {
                return;
            }
            _keyboard.OnKeyDown(static_cast<std::uint8_t>(wParam));
        }
        else if (msg == WM_KEYUP || msg == WM_SYSKEYUP)
        {
            _keyboard.OnKeyUp(static_cast<std::uint8_t>(wParam));
        }
    }

    void Window::HandleRawInputMessage(const LPARAM lParam)
    {
        UINT size = 0;
        const auto hRawInput = std::bit_cast<HRAWINPUT>(lParam);
        if (GetRawInputData(hRawInput, RID_INPUT, nullptr, &size, sizeof(RAWINPUTHEADER)) == static_cast<UINT>(-1))
        {
            return;
        }

        _rawInputBuffer.resize(size);
        if (GetRawInputData(hRawInput, RID_INPUT, _rawInputBuffer.data(), &size, sizeof(RAWINPUTHEADER)) != size)
        {
            return;
        }

        const auto& [header, data] = reinterpret_cast<const RAWINPUT&>(*_rawInputBuffer.data());
        const auto x = data.mouse.lLastX;
        const auto y = data.mouse.lLastY;
        if (header.dwType == RIM_TYPEMOUSE && (x != 0 || y != 0))
        {
            _mouse.OnMoveRaw(x, y);
        }
    }

    void Window::HandleMouseMessage(const UINT msg, const WPARAM wParam, LPARAM lParam)
    {
        const auto [x, y] = MAKEPOINTS(lParam);

        switch (msg)
        {
        case WM_MOUSEMOVE:
            _mouse.OnMove(x, y);
            break;
        case WM_MOUSEWHEEL:
            _mouse.OnWheelDelta(x, y, GET_WHEEL_DELTA_WPARAM(wParam));
            break;
        case WM_LBUTTONDOWN:
            _mouse.OnLeftPressed(x, y);
            break;
        case WM_LBUTTONUP:
            _mouse.OnLeftReleased(x, y);
            break;
        case WM_RBUTTONDOWN:
            _mouse.OnRightPressed(x, y);
            break;
        case WM_RBUTTONUP:
            _mouse.OnRightReleased(x, y);
            break;
        default:
            break;
        }
    }

    std::optional<WPARAM> Window::ProcessMessages()
    {
        MSG msg;

        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                return msg.wParam;
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        return std::nullopt;
    }

    Input::Keyboard& Window::GetKeyboard() noexcept
    {
        return _keyboard;
    }

    Input::Mouse& Window::GetMouse() noexcept
    {
        return _mouse;
    }

    HWND Window::GetWindowHandle() const noexcept
    {
        return _hWnd;
    }

    RECT Window::GetWindowRect(const int width, const int height)
    {
        RECT rect = { .left = 0, .top = 0, .right = width, .bottom = height };
        AdjustWindowRect(&rect, _windowStyle, FALSE);
        return rect;
    }

    void Window::SetTitle(const std::wstring& title) const noexcept
    {
        SetWindowTextW(_hWnd, title.c_str());
    }

    bool Window::IsAutoRepeat(const LPARAM lParam) noexcept
    {
        return (lParam & 0x40000000) != 0;
    }
}
