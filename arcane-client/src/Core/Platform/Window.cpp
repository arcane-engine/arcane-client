#include "Core/Platform/Window.h"

#include "Core/Platform/WindowException.h"

namespace Core::Platform
{
    Window::Window(const int width, const int height) : _windowClass(HandleMessageSetup)
    {
        auto wr = RECT {
            .left = 0,
            .top = 0,
            .right = width,
            .bottom = height
        };
        AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);

        _hWnd = CreateWindow(
            _windowClass.GetName(),
            L"Client",
            WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
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

        ShowWindow(_hWnd, SW_SHOWDEFAULT);
    }

    Window::~Window()
    {
        DestroyWindow(_hWnd);
    }

    LRESULT CALLBACK Window::HandleMessageSetup(const HWND hWnd, const UINT msg, const WPARAM wParam, const LPARAM lParam)
    {
        if (msg == WM_NCCREATE)
        {
            const auto* create = reinterpret_cast<CREATESTRUCT*>(lParam);
            auto* window = static_cast<Window*>(create->lpCreateParams);

            SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
            SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMessageProxy));

            return window->HandleMessage(hWnd, msg, wParam, lParam);
        }

        return DefWindowProc(hWnd, msg, wParam, lParam);
    }

    LRESULT CALLBACK Window::HandleMessageProxy(const HWND hWnd, const UINT msg, const WPARAM wParam, const LPARAM lParam)
    {
        auto* window = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

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

    void Window::SetTitle(const std::wstring& title) const noexcept
    {
        SetWindowTextW(_hWnd, title.c_str());
    }

    bool Window::IsAutoRepeat(const LPARAM lParam) noexcept
    {
        return (lParam & 0x40000000) != 0;
    }
}
