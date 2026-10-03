#pragma once
#include <ios>

namespace Core::IO
{
    class Stream
    {
    public:
        virtual ~Stream() = default;

        virtual std::streamsize Read(char* buffer, std::streamsize size) = 0;
    };
}
