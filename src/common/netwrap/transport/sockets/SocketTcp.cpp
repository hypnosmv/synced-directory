#include "SocketTcp.hpp"
#if defined(__linux__)
    #include <unistd.h>
    #include <sys/socket.h>
#endif


namespace netwrap
{

SocketTcp::~SocketTcp()
{
    if (descriptor_.has_value())
    {
        #if defined(__linux__)
            close(descriptor_.value());
        #endif
    }
}

ISocket::SocketDescriptor SocketTcp::getDescriptor()
{
    if (not descriptor_.has_value())
    {
        #if defined(__linux__)
            descriptor_ = socket(AF_INET, SOCK_STREAM, 0);
        #endif
    }

    return descriptor_.value();
}

} // namespace netwrap
