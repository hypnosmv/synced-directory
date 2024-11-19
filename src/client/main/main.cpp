#include <iostream>
#include <string>
#include <arpa/inet.h>
#include "Socket.hpp"


int main()
{
    Socket socket;

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(1100);

    if (connect(socket.getFd(), (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cerr << "Connection failed" << std::endl;
        return -1;
    }

    std::string message = "Message from client";
    send(socket.getFd(), message.c_str(), message.size(), 0);

    return 0;
}
