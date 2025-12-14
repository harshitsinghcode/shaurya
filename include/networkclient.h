#pragma once
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>

class NetworkClient {
    SOCKET sock;
public:
    NetworkClient(); // Constructor
    ~NetworkClient(); // Destructor to close socket

    // This was missing!
    bool joinMulticast(const std::string& groupIP, int port);
    
    // We keep this for compatibility if you switch back to TCP
    bool connectToServer(const std::string& ip, int port);

    SOCKET getSocket() const { return sock; }
};