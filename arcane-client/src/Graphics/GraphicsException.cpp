#include "Graphics/GraphicsException.h"

#include <format>

#include "Graphics/Device.h"

namespace Graphics
{
    GraphicsException::GraphicsException(const std::string_view message, const HRESULT hResult, const std::source_location& location) noexcept
        : WindowException(message, 0, location), _hResult(hResult)
    {}

    GraphicsException::GraphicsException(const std::string_view message, const HRESULT hResult, const Device& device, const std::source_location& location) noexcept
        : WindowException(message, 0, location), _hResult(hResult)
    {
        for (const auto& informationMessage : device.GetDebugMessages())
        {
            _information += informationMessage + "\n\n";
        }
    }

    const char* GraphicsException::GetType() const noexcept
    {
        return "GraphicsException";
    }

    std::string GraphicsException::GetDescription() const
    {
        auto result = std::format("{}\n\n{}\n{} (Line: {})", what(), TranslateErrorCode(_hResult), _filename, _line);

        if (!_information.empty())
        {
            result += std::format("\n\n{}", _information);
        }

        return result;
    }
}
