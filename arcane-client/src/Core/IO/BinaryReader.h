#pragma once

#include <memory>
#include <string>

namespace Core::IO
{
    class Stream;

    class BinaryReader
    {
    public:
        explicit BinaryReader(std::unique_ptr<Stream> stream);

        [[nodiscard]] int ReadInt() const;
        [[nodiscard]] unsigned int ReadUInt() const;
        [[nodiscard]] float ReadFloat() const;
        [[nodiscard]] std::string ReadString() const;

    private:
        std::unique_ptr<Stream> _stream;
    };
}
