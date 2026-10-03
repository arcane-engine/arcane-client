#pragma once

#include <Windows.h>

#include "Core/Platform/WindowException.h"
#include "Graphics/Device.h"

namespace Graphics
{
    class GraphicsException : public Core::Platform::WindowException
    {
    public:
        GraphicsException(const std::string& message, HRESULT hResult, const std::source_location& location = std::source_location::current()) noexcept;
        GraphicsException(const std::string& message, HRESULT hResult, const Device& device, const std::source_location& location = std::source_location::current()) noexcept;

        [[nodiscard]] std::string GetType() const noexcept override;
        [[nodiscard]] std::string GetDescription() const noexcept override;

    private:
        HRESULT _hResult;
        std::string _information;
    };
}
