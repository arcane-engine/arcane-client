#pragma once

#include <optional>
#include <string>

#include "Core/Input/Keyboard.h"
#include "Core/Platform/WindowClass.h"


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

        void SetTitle(const std::wstring& title) const noexcept;

    private:
        static LRESULT CALLBACK HandleMessageSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
        static LRESULT CALLBACK HandleMessageProxy(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

        [[nodiscard]] LRESULT HandleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

        static void HandleSystemMessage(UINT msg) noexcept;
        void HandleKeyboardMessage(UINT msg, WPARAM wParam, LPARAM lParam);

        [[nodiscard]] static bool IsAutoRepeat(LPARAM lParam) noexcept;

    private:
        WindowClass _windowClass;
        HWND _hWnd;
        Input::Keyboard _keyboard;
    };
}
