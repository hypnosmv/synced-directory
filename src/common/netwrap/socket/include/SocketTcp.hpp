#pragma once
#include <optional>

#include "interfaces/ISocket.hpp"


namespace netwrap
{

class SocketTcp : public ISocket
{
public:
    ~SocketTcp();

    ISocket::SocketDescriptor getDescriptor() override;

private:
    std::optional<ISocket::SocketDescriptor> descriptor_;
};

} // namespace netwrap
