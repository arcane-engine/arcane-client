#pragma once

#define WIN32_LEAN_AND_MEAN

#include <span>
#include <windows.h>

#include "Platform/WindowException.h"

namespace Graphics
{
    class GraphicsException : public Platform::WindowException
    {
    public:
        GraphicsException(std::string_view message, HRESULT hResult, const std::source_location& location = std::source_location::current()) noexcept;
        GraphicsException(std::string_view message, HRESULT hResult, std::span<const std::string> debugMessages, const std::source_location& location = std::source_location::current()) noexcept;

        [[nodiscard]] const char* GetType() const noexcept override;
        [[nodiscard]] std::string GetDescription() const override;

    private:
        HRESULT _hResult;
        std::string _information;
    };
}
