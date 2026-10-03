#pragma once

#include <fstream>
#include <string>

#include "Stream.h"

namespace Core::IO
{
    class FileStream final : public Stream
    {
    public:
        explicit FileStream(const std::string& path);

        std::streamsize Read(char* buffer, std::streamsize size) override;

    private:
        std::string _path;
        std::ifstream _stream;
    };
}
