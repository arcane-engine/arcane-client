#pragma once

#include <string>
#include <source_location>

namespace Core
{
    class Exception : public std::exception
    {
    public:
        explicit Exception(std::string_view message, const std::source_location& location = std::source_location::current());

        [[nodiscard]] const char* what() const noexcept override;

        [[nodiscard]] virtual std::string GetType() const noexcept;
        [[nodiscard]] virtual std::string GetDescription() const noexcept;

    protected:
        const char* _filename;
        std::uint32_t _line;

    private:
        std::string _message;
    };
}
