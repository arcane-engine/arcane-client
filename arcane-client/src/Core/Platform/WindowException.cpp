#include "Core/Platform/WindowException.h"

#include <Windows.h>
#include <format>

namespace Core::Platform
{
    WindowException::WindowException(const std::string_view message, const uint32_t errorCode, const std::source_location& location)
        : Exception(message, location), _errorCode(errorCode)
    {}

    std::string WindowException::GetType() const noexcept
    {
        return "WindowException";
    }

    std::string WindowException::GetDescription() const noexcept
    {
        return std::format("{}\n\n{}\n\n{} (Line: {})", what(), TranslateErrorCode(_errorCode), _filename, _line);
    }

    uint32_t WindowException::GetErrorCode() const noexcept
    {
        return _errorCode;
    }

    std::string WindowException::TranslateErrorCode(const uint32_t errorCode) noexcept
    {
        char* pMessageBuffer = nullptr;
        const auto length = FormatMessageA(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
            nullptr,
            errorCode,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            reinterpret_cast<LPSTR>(&pMessageBuffer),
            0,
            nullptr
        );

        if (length == 0)
        {
            return "Undefined error code";
        }

        std::string result = pMessageBuffer;
        LocalFree(pMessageBuffer);

        while (!result.empty() && (result.back() == '\r' || result.back() == '\n'))
        {
            result.pop_back();
        }

        return result;
    }
}