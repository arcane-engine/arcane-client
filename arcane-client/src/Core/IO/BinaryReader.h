#pragma once

#include <fstream>
#include <vector>

#include "Stream.h"

namespace Core::IO
{
    class BinaryReader
    {
    public:
        explicit BinaryReader(std::unique_ptr<Stream> stream);

        [[nodiscard]] static BinaryReader FromFile(std::string_view path);

        template<typename T>
        [[nodiscard]] T Read();
        template<typename T>
        [[nodiscard]] std::vector<T> Read(std::size_t count);

    private:
        std::unique_ptr<Stream> _stream;
    };
}

#include "Core/IO/BinaryReader.inl"