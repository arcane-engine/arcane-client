#pragma once

#include <fstream>
#include <string>

#include "Core/IO/Stream.h"

namespace Core::IO
{
    class FileStream final : public Stream
    {
    public:
        explicit FileStream(std::string_view path);

        std::streamsize Read(char* buffer, std::streamsize size) override;

    private:
        std::string _path;
        std::ifstream _stream;
    };
}
