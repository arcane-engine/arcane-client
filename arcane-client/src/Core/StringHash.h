#pragma once

#include <string_view>

namespace Core
{
    struct StringHash
    {
        using is_transparent = void;

        std::size_t operator()(std::string_view sv) const noexcept;
    };
}
