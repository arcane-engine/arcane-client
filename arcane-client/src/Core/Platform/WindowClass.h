#pragma once

#include <Windows.h>

namespace Core::Platform
{
    class WindowClass
    {
    public:
        explicit WindowClass(WNDPROC handleMessageSetup);
        WindowClass(const WindowClass&) = delete;
        WindowClass(WindowClass&&) = delete;

        ~WindowClass();

        WindowClass& operator=(const WindowClass&) = delete;
        WindowClass& operator=(WindowClass&&) = delete;

        [[nodiscard]] LPCWSTR GetName() const noexcept;
        [[nodiscard]] HINSTANCE GetInstance() const noexcept;

    private:
        LPCWSTR _name;
        HINSTANCE _hInstance;
    };
}
