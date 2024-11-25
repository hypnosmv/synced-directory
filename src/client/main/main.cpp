#include <iostream>
#include <string>
#include <arpa/inet.h>
#include <memory>

#include "protocol/ProtocolFactoryTcp.hpp"
#include "IPv4.hpp"
#include "Port.hpp"


int main()
{
    std::shared_ptr<netwrap::IProtocolFactory> protocolFactory = std::make_shared<netwrap::ProtocolFactoryTcp>();
    std::shared_ptr<netwrap::ISocket> socket = protocolFactory->createSocket();

    netwrap::IPv4 ip("127.0.0.1");
    netwrap::Port port(1100);

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = ip.getFamily();
    serv_addr.sin_addr.s_addr = ip.getAddress();
    serv_addr.sin_port = port.getPort();

    if (connect(socket->getDescriptor(), (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cerr << "Connection failed" << std::endl;
        return -1;
    }

    std::string message = "Message from client";
    send(socket->getDescriptor(), message.c_str(), message.size(), 0);

    return 0;
}
