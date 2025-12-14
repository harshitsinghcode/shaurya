#pragma once
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>

class NetworkClient {
    SOCKET sock;
public:
    NetworkClient();
    ~NetworkClient(); 

    bool joinMulticast(const std::string& groupIP, int port);
    
    bool connectToServer(const std::string& ip, int port);

    SOCKET getSocket() const { return sock; }
};