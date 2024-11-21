#include "SocketTcp.hpp"
#include <unistd.h>
#include <sys/socket.h>


namespace netwrap
{

SocketTcp::~SocketTcp()
{
    if (descriptor_.has_value())
    {
        close(descriptor_.value());
    }
}

ISocket::SocketDescriptor SocketTcp::getDescriptor()
{
    if (not descriptor_.has_value())
    {
        descriptor_ = socket(AF_INET, SOCK_STREAM, 0);
    }

    return descriptor_.value();
}

} // namespace netwrap
