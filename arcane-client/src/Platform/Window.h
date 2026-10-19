#pragma once

#include <memory>
#include <optional>

#include "Core/Context/Context.h"
#include "Core/Input/Keyboard.h"
#include "Core/Input/Mouse.h"
#include "Graphics/Device.h"
#include "Platform/WindowClass.h"

namespace Platform
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

        [[nodiscard]] Core::Input::Keyboard& GetKeyboard() noexcept;
        [[nodiscard]] Core::Input::Mouse& GetMouse() noexcept;
        [[nodiscard]] HWND GetWindowHandle() const noexcept;
        [[nodiscard]] int GetWidth() const noexcept;
        [[nodiscard]] int GetHeight() const noexcept;

        void Update(const Core::Context& context);

        void ToggleFullscreen();

        void CaptureMouse();
        void ReleaseMouse();

    private:
        static void RegisterRawMouseInputDevice();
        static LRESULT CALLBACK HandleMessageSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
        static LRESULT CALLBACK HandleMessageProxy(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

        [[nodiscard]] LRESULT HandleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

        void HandleSystemMessage(UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
        void HandleKeyboardMessage(UINT msg, WPARAM wParam, LPARAM lParam);
        void HandleRawInputMessage(UINT msg, LPARAM lParam);
        void HandleMouseMessage(UINT msg, WPARAM wParam, LPARAM lParam);

        [[nodiscard]] static RECT GetAdjustedWindowRect(int width, int height);

        [[nodiscard]] static bool IsAutoRepeat(LPARAM lParam) noexcept;

    private:
        static constexpr DWORD _windowStyle = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;

        WindowClass _windowClass;
        HWND _hWnd;
        Core::Input::Keyboard _keyboard;
        Core::Input::Mouse _mouse;
        POINT _mousePosistion{};
        std::vector<std::uint8_t> _rawInputBuffer;
        int _width;
        int _height;
        RECT _windowRect = {};
        bool _fullscreen = false;
    };
}
