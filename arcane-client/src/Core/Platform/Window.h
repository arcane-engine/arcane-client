#pragma once

#include <optional>

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

    private:
        static LRESULT CALLBACK HandleMessageSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
        static LRESULT CALLBACK HandleMessageProxy(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

        [[nodiscard]] LRESULT HandleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

        static void HandleSystemMessage(UINT msg) noexcept;

    private:
        WindowClass _windowClass;
        HWND _hWnd;
    };
}
