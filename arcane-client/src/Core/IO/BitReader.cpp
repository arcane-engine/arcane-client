#include "BitReader.h"

namespace Core::IO
{
    BitReader::BitReader(const std::uint8_t* buffer)
        : _buffer(buffer)
    {}

    bool BitReader::ReadBit()
    {
        const int byteIndex = _offset / 8;
        const int bitIndex = 7 - (_offset % 8);
        _offset++;

        return (_buffer[byteIndex] & (1 << bitIndex)) != 0;
    }

    std::uint8_t BitReader::ReadByte()
    {
        std::uint8_t value = 0;
        for (int i = 0; i < 8; ++i)
        {
            value = static_cast<std::uint8_t>((value << 1) | (ReadBit() ? 1 : 0));
        }
        return value;
    }

    std::uint16_t BitReader::ReadUnsignedShort()
    {
        std::uint16_t value = 0;
        for (int i = 0; i < 16; ++i)
        {
            value = static_cast<std::uint16_t>((value << 1) | (ReadBit() ? 1 : 0));
        }
        return value;
    }

    void BitReader::Skip(const int bits)
    {
        _offset += bits;
    }

    int BitReader::GetOffset() const
    {
        return _offset;
    }
}
