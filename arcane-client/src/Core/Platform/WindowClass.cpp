#include "Core/Platform/WindowClass.h"

#include "Core/Platform/WindowException.h"

namespace Core::Platform
{
    WindowClass::WindowClass(const WNDPROC handleMessageSetup)
        : _name(L"arcane-client"), _hInstance(GetModuleHandle(nullptr))
    {
        WNDCLASSEX wc = {};

        wc.cbSize = sizeof(wc);
        wc.style = CS_OWNDC;
        wc.lpfnWndProc = handleMessageSetup;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hInstance = _hInstance;
        wc.hIcon = nullptr;
        wc.hCursor = nullptr;
        wc.hbrBackground = nullptr;
        wc.lpszMenuName = nullptr;
        wc.lpszClassName = GetName();

        if (RegisterClassEx(&wc) == 0)
        {
            throw WindowException("Register window class failed.", GetLastError());
        }
    }

    WindowClass::~WindowClass()
    {
        UnregisterClass(GetName(), _hInstance);
    }

    LPCWSTR WindowClass::GetName() const noexcept
    {
        return _name;
    }

    HINSTANCE WindowClass::GetInstance() const noexcept
    {
        return _hInstance;
    }
}
