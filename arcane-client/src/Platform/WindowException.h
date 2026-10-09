#pragma once

#include <source_location>
#include <string>

#include "Core/Common/Exception.h"

namespace Platform
{
    class WindowException : public Core::Exception
    {
    public:
        WindowException(std::string_view message, std::uint32_t errorCode, const std::source_location& location = std::source_location::current());

        [[nodiscard]] const char* GetType() const noexcept override;
        [[nodiscard]] std::string GetDescription() const override;

        [[nodiscard]] std::uint32_t GetErrorCode() const noexcept;
        [[nodiscard]] static std::string TranslateErrorCode(std::uint32_t errorCode) noexcept;

    private:
        std::uint32_t _errorCode;
    };
}
