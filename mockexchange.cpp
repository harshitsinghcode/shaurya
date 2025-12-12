#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <winsock2.h>
#include <windows.h>
#pragma comment(lib, "ws2_32.lib") 
void startServer() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(5000);

    bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, 1);

    std::cout << "[EXCHANGE] Market Open. Waiting for connections on Port 5000...\n";

    int addrLen = sizeof(serverAddr);
    SOCKET clientSocket = accept(serverSocket, (sockaddr*)&serverAddr, &addrLen);
    std::cout << "[EXCHANGE] Trader Connected! Sending Market Data...\n";
    std::vector<std::string> messages = {
        "8=FIX.4.2|35=X|55=AAPL|269=0|270=150.50|",
        "8=FIX.4.2|35=X|55=GOOGL|269=0|270=2800.10|",
        "8=FIX.4.2|35=X|55=AAPL|269=1|270=150.55|",
        "8=FIX.4.2|35=X|55=MSFT|269=0|270=299.00|",
        "8=FIX.4.2|35=X|55=AAPL|269=0|270=150.60|"
    };

    for (int i = 0; i < 50; i++) {
        std::string raw = messages[i % messages.size()];
                for (char &c : raw) {
            if (c == '|') c = '\x01';
        }
        send(clientSocket, raw.c_str(), raw.length(), 0);
        Sleep(100);
    }

    std::cout << "[EXCHANGE] Market Closed.\n";
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();
}

int main() {
    startServer();
    return 0;
}