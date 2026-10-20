#pragma once

#include "Core/IO/FileStream.h"
#include "Core/IO/BinaryReader.h"

namespace Core::IO
{
    inline BinaryReader::BinaryReader(std::unique_ptr<Stream> stream)
        : _stream(std::move(stream))
    {}

    inline BinaryReader BinaryReader::FromFile(std::string_view path)
    {
        return BinaryReader(std::make_unique<FileStream>(path));
    }

    template <typename T>
    T BinaryReader::Read()
    {
        if constexpr (std::is_same_v<T, std::string>)
        {
            const  auto length = Read<std::uint32_t>();
            std::string value(length, '\0');
            _stream->Read(value.data(), length);
            return value;
        }
        else
        {
            T value{};
            _stream->Read(reinterpret_cast<char*>(&value), sizeof(T));
            return value;
        }
    }

    template <typename T>
    std::vector<T> BinaryReader::Read(std::size_t count)
    {
        std::vector<T> buffer(count);
        _stream->Read(reinterpret_cast<char*>(buffer.data()), static_cast<std::streamsize>(count * sizeof(T)));
        return buffer;
    }
}
