#include "Core/IO/BinaryReader.h"

#include "Core/IO/Stream.h"

namespace Core::IO
{
    BinaryReader::BinaryReader(std::unique_ptr<Stream> stream)
        : _stream(std::move(stream))
    {}

    int BinaryReader::ReadInt() const
    {
        int value = 0;

        _stream->Read(reinterpret_cast<char*>(&value), sizeof(value));

        return value;
    }

    unsigned int BinaryReader::ReadUInt() const
    {
        unsigned int value = 0;

        _stream->Read(reinterpret_cast<char*>(&value), sizeof(value));

        return value;
    }

    float BinaryReader::ReadFloat() const
    {
        float value = 0.0f;

        _stream->Read(reinterpret_cast<char*>(&value), sizeof(value));

        return value;
    }

    std::string BinaryReader::ReadString() const
    {
        unsigned int length = {};

        _stream->Read(reinterpret_cast<char*>(&length), sizeof(length));
        std::string result(length, '\0');
        _stream->Read(result.data(), length);

        return result;
    }
}
