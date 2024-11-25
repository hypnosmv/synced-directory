#pragma once
#if defined(__linux__)
    #include <netinet/in.h>
#endif


namespace netwrap
{

class IIP
{
public:
    #if defined(__linux__)
        using Family = uint16_t;
        using Address = uint32_t;
    #endif

    virtual ~IIP() = default;

    virtual Family getFamily() = 0;
    virtual Address getAddress() = 0;
};

} // namespace netwrap
