#include "Socket.hpp"
#include <unistd.h>
#include <sys/socket.h>


Socket::Socket()
    : fd_(socket(AF_INET, SOCK_STREAM, 0))
{
}

Socket::~Socket()
{
    close(fd_);
}

int Socket::getFd() const
{
    return fd_;
}
