#include "Core/IO/FileStream.h"

#include <format>

namespace Core::IO
{
    FileStream::FileStream(const std::string_view path)
        : _path(path), _stream(_path, std::ios::binary | std::ios::in)
    {
        if (!_stream.is_open())
        {
            throw std::runtime_error(std::format("Failed to open file '{}'.", path));
        }
    }

    std::streamsize FileStream::Read(char* buffer, const std::streamsize size)
    {
        _stream.read(buffer, size);
        return _stream.gcount();
    }
}
