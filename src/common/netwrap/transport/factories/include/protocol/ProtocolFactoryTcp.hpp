#pragma once
#include "interfaces/IProtocolFactory.hpp"


namespace netwrap
{

class ProtocolFactoryTcp : public IProtocolFactory
{
public:
    std::shared_ptr<ISocket> createSocket() const override;
};

} // namespace netwrap
