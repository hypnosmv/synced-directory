#pragma once
#include <cstdint>


namespace netwrap
{

class Port
{
public:
    #if defined(__linux__)
        using Type = uint16_t;
    #endif

    explicit Port(int port);

    Type getPort() const;

private:
    Type port_;
};

} // namespace netwrap
