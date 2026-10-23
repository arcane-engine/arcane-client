#pragma once

#include <string>

#include "Math/Vector3.h"

namespace Core::IO
{
    class BitReader
    {
    public:
        explicit BitReader(const std::uint8_t* buffer);

        [[nodiscard]] bool ReadBit();
        [[nodiscard]] std::uint8_t ReadByte();
        [[nodiscard]] std::uint16_t ReadUnsignedShort();
        [[nodiscard]] float ReadFloat();
        [[nodiscard]] std::array<float, 3> ReadFloat3();
        [[nodiscard]] std::array<float, 4> ReadFloat4();
        [[nodiscard]] std::string ReadString();

        void Skip(int bits);

        [[nodiscard]] int GetOffset() const;

    private:
        const std::uint8_t* _buffer;
        int _offset = 0;
    };
}
