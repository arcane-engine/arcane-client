#pragma once

#include <source_location>
#include <string>

#include "Core/Exception.h"

namespace Core::Platform
{
    class WindowException : public Exception
    {
    public:
        WindowException(std::string_view message, uint32_t errorCode, const std::source_location& location = std::source_location::current());

        [[nodiscard]] const char* GetType() const noexcept override;
        [[nodiscard]] std::string GetDescription() const override;

        [[nodiscard]] uint32_t GetErrorCode() const noexcept;
        [[nodiscard]] static std::string TranslateErrorCode(uint32_t errorCode) noexcept;

    private:
        uint32_t _errorCode;
    };
}
