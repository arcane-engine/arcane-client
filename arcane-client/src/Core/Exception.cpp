#include "Core/Exception.h"

#include <format>

namespace Core
{
    Exception::Exception(const std::string_view message, const std::source_location& location)
        : _filename(location.file_name()), _line(location.line()), _message(message)
    {}

    const char* Exception::what() const noexcept
    {
        return _message.c_str();
    }

    std::string Exception::GetType() const noexcept
    {
        return "Exception";
    }

    std::string Exception::GetDescription() const noexcept
    {
        return std::format("{}\n\n{} (Line: {})", _message, _filename, _line);
    }
}