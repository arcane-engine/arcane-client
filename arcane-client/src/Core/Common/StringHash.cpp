
#include "Core/Common/StringHash.h"

namespace Core
{
    std::size_t StringHash::operator()(const std::string_view sv) const noexcept
    {
        return std::hash<std::string_view>{}(sv);
    }
}
