#pragma once

#include <Windows.h>

#include "Core/Platform/WindowException.h"
#include "Graphics/Device.h"

namespace Graphics
{
    class GraphicsException : public Core::Platform::WindowException
    {
    public:
        GraphicsException(std::string_view message, HRESULT hResult, const std::source_location& location = std::source_location::current()) noexcept;
        GraphicsException(std::string_view message, HRESULT hResult, const Device& device, const std::source_location& location = std::source_location::current()) noexcept;

        [[nodiscard]] const char* GetType() const noexcept override;
        [[nodiscard]] std::string GetDescription() const override;

    private:
        HRESULT _hResult;
        std::string _information;
    };
}
