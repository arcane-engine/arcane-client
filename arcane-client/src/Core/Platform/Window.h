#pragma once

#include <memory>
#include <optional>

#include "Core/Input/Keyboard.h"
#include "Core/Input/Mouse.h"
#include "Core/Platform/WindowClass.h"
#include "Graphics/Device.h"

namespace Core::Platform
{
    class Window
    {
    public:
        Window(int width, int height);
        ~Window();

        Window(const Window&) = delete;
        Window(Window&&) = delete;
        Window& operator=(const Window&) = delete;
        Window& operator=(Window&&) = delete;

        [[nodiscard]] static std::optional<WPARAM> ProcessMessages();

        [[nodiscard]] Input::Keyboard& GetKeyboard() noexcept;
        [[nodiscard]] Input::Mouse& GetMouse() noexcept;
        [[nodiscard]] HWND GetWindowHandle() const noexcept;
        [[nodiscard]] int GetWidth() const noexcept;
        [[nodiscard]] int GetHeight() const noexcept;

        void ToggleFullscreen();

    private:
        static void RegisterRawMouseInputDevice();
        static void CaptureMouseCursor(int width, int height);

        static LRESULT CALLBACK HandleMessageSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
        static LRESULT CALLBACK HandleMessageProxy(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

        [[nodiscard]] LRESULT HandleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

        void HandleSystemMessage(UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
        void HandleKeyboardMessage(UINT msg, WPARAM wParam, LPARAM lParam);
        void HandleRawInputMessage(LPARAM lParam);
        void HandleMouseMessage(UINT msg, WPARAM wParam, LPARAM lParam);

        static RECT GetAdjustedWindowRect(int width, int height);

        [[nodiscard]] static bool IsAutoRepeat(LPARAM lParam) noexcept;

    private:
        static constexpr DWORD _windowStyle = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;

        WindowClass _windowClass;
        HWND _hWnd;
        Input::Keyboard _keyboard;
        Input::Mouse _mouse;
        std::vector<std::uint8_t> _rawInputBuffer;
        int _width;
        int _height;
        RECT _windowRect = {};
        bool _fullscreen = false;
    };
}
