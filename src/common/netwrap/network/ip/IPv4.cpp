#include "IPv4.hpp"
#if defined(__linux__)
    #include <arpa/inet.h>
#endif


namespace netwrap
{

IPv4::IPv4()
{
    #if defined(__linux__)
        family_ = AF_INET;
        address_ = INADDR_ANY;
    #endif
}

IPv4::IPv4(const std::string& address)
{
    #if defined(__linux__)
        family_ = AF_INET;
        address_ = inet_addr(address.c_str());
    #endif
}

IIP::Family IPv4::getFamily()
{
    return family_;
}

IIP::Address IPv4::getAddress()
{
    return address_;
}

} // namespace netwrap
