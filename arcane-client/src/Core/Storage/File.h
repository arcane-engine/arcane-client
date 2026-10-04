#pragma once

#include <string>
#include <vector>

namespace Core
{
    class File
    {
    public:
        static std::vector<unsigned char> Read(std::string_view path);
    };
}

