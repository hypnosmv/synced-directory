#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <memory>

#include "protocol/ProtocolFactoryTcp.hpp"
#include "IPv4.hpp"
#include "Port.hpp"


int main()
{
    std::shared_ptr<netwrap::IProtocolFactory> protocolFactory = std::make_shared<netwrap::ProtocolFactoryTcp>();
    std::shared_ptr<netwrap::ISocket> serverSocket = protocolFactory->createSocket();

    netwrap::IPv4 anyIp;
    netwrap::Port port(1100);

    struct sockaddr_in address;
    address.sin_family = anyIp.getFamily();
    address.sin_addr.s_addr = anyIp.getAddress();
    address.sin_port = port.getPort();

    if (bind(serverSocket->getDescriptor(), (struct sockaddr*)&address, sizeof(address)) < 0)
    {
        std::cerr << "Bind failed" << std::endl;
        return -1;
    }

    if (listen(serverSocket->getDescriptor(), 3) < 0)
    {
        std::cerr << "Listen failed" << std::endl;
        return -1;
    }

    int clientSocket = accept(serverSocket->getDescriptor(), NULL, NULL);
    if (clientSocket < 0)
    {
        std::cerr << "Accept failed" << std::endl;
        return -1;
    }

    char buffer[1024] = {0};
    if (read(clientSocket, buffer, 1024) > 0)
    {
        std::cout << "Received: " << buffer << std::endl;
    }

    return 0;
}
