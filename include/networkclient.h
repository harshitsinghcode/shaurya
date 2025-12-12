#pragma once
#include <string>
#include <functional>
#include <winsock2.h>
#include <windows.h>
using DataCallback = std::function<void(const char*, size_t)>;

class NetworkClient {
    SOCKET sock;
public:
    bool connectToServer(const std::string& ip, int port);
    void startListenLoop(DataCallback onData); 
    SOCKET getSocket() const { return sock; }
};