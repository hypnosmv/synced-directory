#include "Port.hpp"
#if defined(__linux__)
    #include <arpa/inet.h>
#endif


namespace netwrap
{

Port::Port(int port)
{
    #if defined(__linux__)
        port_ = htons(port);
    #endif
}

Port::Type Port::getPort() const
{
    return port_;
}

} // namespace netwrap
