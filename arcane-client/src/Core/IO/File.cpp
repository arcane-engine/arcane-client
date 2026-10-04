#include "Core/IO/File.h"

#include <filesystem>
#include <format>
#include <fstream>

#include "Core/Common/Exception.h"

namespace Core
{
    std::vector<unsigned char> File::Read(std::string_view path)
    {
        auto file = std::ifstream(std::filesystem::path(path), std::ios::binary | std::ios::ate);
        if (!file)
        {
            throw Exception(std::format("Failed to open file '{}'.", path));
        }

        const auto size = file.tellg();
        file.seekg(0, std::ios::beg);

        std::vector<unsigned char> buffer(size);
        if (file.read(reinterpret_cast<char*>(buffer.data()), size))
        {
            return buffer;
        }

        throw Exception(std::format("Failed to read file '{}'.", path));
    }
}
