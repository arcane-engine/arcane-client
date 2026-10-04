#pragma once

#include <ios>

namespace Core::IO
{
    class Stream
    {
    public:
        Stream() = default;

        virtual ~Stream() = default;

        Stream(const Stream&) = delete;
        Stream& operator=(const Stream&) = delete;

        Stream(Stream&&) = delete;
        Stream& operator=(Stream&&) = delete;

        virtual std::streamsize Read(char* buffer, std::streamsize size) = 0;
    };
}
