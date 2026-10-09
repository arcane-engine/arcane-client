#pragma once

#include <span>
#include <cstdint>

namespace Core::IO
{
    class BitReader
    {
    public:
        explicit BitReader(const std::uint8_t* buffer);

        [[nodiscard]] bool ReadBit();
        [[nodiscard]] std::uint8_t ReadByte();
        [[nodiscard]] std::uint16_t ReadUnsignedShort();

        void Skip(int bits);

        [[nodiscard]] int GetOffset() const;

    private:
        const std::uint8_t* _buffer;
        int _offset = 0;
    };
}