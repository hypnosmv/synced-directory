#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <memory>

#include "SocketTcp.hpp"


int main()
{
    std::shared_ptr<netwrap::ISocket> serverSocket = std::make_shared<netwrap::SocketTcp>();

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(1100);

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
