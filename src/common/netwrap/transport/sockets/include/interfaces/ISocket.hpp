#pragma once


namespace netwrap
{

class ISocket
{
public:
    #if defined(__linux__)
        using SocketDescriptor = int;
    #endif

    virtual ~ISocket() = default;

    virtual SocketDescriptor getDescriptor() = 0;
};

} // namespace netwrap
