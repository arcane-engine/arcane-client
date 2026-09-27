#include "Core/Storage/File.h"

#include <format>
#include <fstream>

#include "Core/Exception.h"

namespace Core
{
    std::vector<unsigned char> File::Read(const std::string& path)
    {
        auto file = std::ifstream(path, std::ios::binary | std::ios::ate);
        if (!file)
        {
            throw Exception(std::format("Failed to open file '{}'.", path));
        }

        const auto size = file.tellg();
        file.seekg(0, std::ios::beg);

        std::vector<unsigned char> buffer(size);
        if (file.read(reinterpret_cast<char*>(buffer.data()), size))
        {
            return std::move(buffer);
        }

        throw Exception(std::format("Failed to read file '{}'.", path));
    }
}
