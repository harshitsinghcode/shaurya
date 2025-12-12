#include "../include/NetworkClient.h"
#include <iostream>

bool NetworkClient::connectToServer(const std::string& ip, int port) {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    sock = socket(AF_INET, SOCK_STREAM, 0); 
    
    u_long mode = 1;
    ioctlsocket(sock, FIONBIO, &mode);

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(ip.c_str());
    serverAddr.sin_port = htons(port);

    connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr));
    fd_set writeSet;
    FD_ZERO(&writeSet);
    FD_SET(sock, &writeSet);
    timeval timeout = { 2, 0 }; 
    int selectResult = select(0, NULL, &writeSet, NULL, &timeout);
    
    return (selectResult > 0);
}

void NetworkClient::startListenLoop(DataCallback onData) {
}