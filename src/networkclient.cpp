#include "../include/NetworkClient.h"
#include "../include/Logger.h"
#include <iostream>

NetworkClient::NetworkClient() : sock(INVALID_SOCKET) {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
}

NetworkClient::~NetworkClient() {
    if (sock != INVALID_SOCKET) {
        closesocket(sock);
    }
    WSACleanup();
}

bool NetworkClient::joinMulticast(const std::string& groupIP, int port) {
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    
    char reuse = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    sockaddr_in localAddr;
    localAddr.sin_family = AF_INET;
    localAddr.sin_port = htons(port);
    localAddr.sin_addr.s_addr = htonl(INADDR_ANY); 

    if (bind(sock, (sockaddr*)&localAddr, sizeof(localAddr)) < 0) {
        return false;
    }

    ip_mreq mreq;
    mreq.imr_multiaddr.s_addr = inet_addr(groupIP.c_str());
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);
    
    if (setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&mreq, sizeof(mreq)) < 0) {
        return false;
    }

    // Non-blocking mode
    u_long mode = 1;
    ioctlsocket(sock, FIONBIO, &mode);

    return true;
}

bool NetworkClient::connectToServer(const std::string& ip, int port) {
    sock = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(ip.c_str());

    if (connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        return false;
    }
    
    u_long mode = 1;
    ioctlsocket(sock, FIONBIO, &mode);
    return true;
}