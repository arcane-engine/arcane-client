#pragma once

#include <memory>
#include <optional>
#include <string>

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
        [[nodiscard]] Graphics::Device& GetDevice() const;

        void SetTitle(const std::wstring& title) const noexcept;

    private:
        static void RegisterRawMouseInputDevice();
        static void CaptureMouseCursor(int width, int height);

        static LRESULT CALLBACK HandleMessageSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
        static LRESULT CALLBACK HandleMessageProxy(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

        [[nodiscard]] LRESULT HandleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

        static void HandleSystemMessage(UINT msg) noexcept;
        void HandleKeyboardMessage(UINT msg, WPARAM wParam, LPARAM lParam);
        void HandleRawInputMessage(LPARAM lParam);
        void HandleMouseMessage(UINT msg, WPARAM wParam, LPARAM lParam);

        static RECT GetWindowRect(int width, int height);

        [[nodiscard]] static bool IsAutoRepeat(LPARAM lParam) noexcept;

    private:
        WindowClass _windowClass;
        HWND _hWnd;
        Input::Keyboard _keyboard;
        Input::Mouse _mouse;
        std::vector<std::uint8_t> _rawInputBuffer;
        std::unique_ptr<Graphics::Device> _device;
    };
}
