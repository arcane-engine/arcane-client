#pragma once

#include <Windows.h>

#include "Core/Platform/WindowException.h"

namespace Graphics
{
    class Device;

    class GraphicsException : public Core::Platform::WindowException
    {
    public:
        GraphicsException(const std::string& message, HRESULT hResult, const std::source_location& location = std::source_location::current()) noexcept;
        GraphicsException(const std::string& message, HRESULT hResult, Device& device, const std::source_location& location = std::source_location::current()) noexcept;

        [[nodiscard]] std::string GetType() const noexcept override;
        [[nodiscard]] std::string GetDescription() const noexcept override;

    private:
        HRESULT _hResult;
        std::string _information;
    };
}
