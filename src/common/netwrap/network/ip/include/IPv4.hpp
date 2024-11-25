#pragma once
#include <string>

#include "interfaces/IIP.hpp"


namespace netwrap
{

class IPv4 : public IIP
{
public:
    IPv4();
    explicit IPv4(const std::string& address);

    IIP::Family getFamily() override;
    IIP::Address getAddress() override;

private:
    IIP::Family family_;
    IIP::Address address_;
};

} // namespace netwrap
