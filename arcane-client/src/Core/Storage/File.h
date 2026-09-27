#pragma once

#include <string>
#include <vector>

namespace Core
{
    class File
    {
    public:
        static std::vector<unsigned char> Read(const std::string& path);
    };
}

