#include "FileStream.h"

namespace Core::IO
{
    FileStream::FileStream(const std::string& path)
        : _path(path), _stream(path, std::ios::binary | std::ios::in)
    {}

    std::streamsize FileStream::Read(char* buffer, const std::streamsize size)
    {
        _stream.read(buffer, size);
        return _stream.gcount();
    }
}
