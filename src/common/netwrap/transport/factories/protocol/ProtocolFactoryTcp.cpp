#include "protocol/ProtocolFactoryTcp.hpp"
#include "SocketTcp.hpp"


namespace netwrap
{

std::shared_ptr<ISocket> ProtocolFactoryTcp::createSocket() const
{
    return std::make_shared<SocketTcp>();
}

} // namespace netwrap
