#pragma once
#include <memory>

#include "interfaces/ISocket.hpp"


namespace netwrap
{

class IProtocolFactory
{
public:
    virtual ~IProtocolFactory() = default;

    virtual std::shared_ptr<ISocket> createSocket() const = 0;
};

} // namespace netwrap
