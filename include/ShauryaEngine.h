#pragma once
#include <string>
#include <thread>
#include <atomic>
#include <iostream>
#include "NetworkClient.h"
#include "LockFreeQueue.h"
#include "FixParser.h"
#include "Stats.h"
#include "Logger.h"

class ShauryaEngine {
    std::thread processorThread;
    std::thread networkThread;
    std::atomic<bool> running;
    NetworkClient client;
    LockFreeQueue<FixMessage, 1024> messageQueue; 
public:
    ShauryaEngine() : running(false) {}

    ~ShauryaEngine() {
        stop();
    }

    bool start(const std::string& ip, int port) {
        if (running) return false;
        running = true;

        processorThread = std::thread(&ShauryaEngine::processorLoop, this);

        if (!client.joinMulticast(ip, port)) {
            std::cerr << "[C++] Failed to join multicast.\n";
            running = false;
            if (processorThread.joinable()) processorThread.join();
            return false;
        }

        networkThread = std::thread(&ShauryaEngine::networkLoop, this);
        
        std::cout << "[C++] Engine Started. Listening on " << ip << ":" << port << "\n";
        return true;
    }

    void stop() {
        running = false;
        if (processorThread.joinable()) processorThread.join();
        if (networkThread.joinable()) networkThread.join();
        std::cout << "[C++] Engine Stopped.\n";
    }

    double getMinLatency() {
        if (Stats::latencies.empty()) return 0.0;
        return Stats::latencies.back(); 
    }

private:
    void processorLoop() {
        FixMessage msg;
        while (running) {
            if (messageQueue.pop(msg)) {
                FixParser::parse(msg);
            } else {
                 std::this_thread::sleep_for(std::chrono::nanoseconds(100));}
        }
    }

    void networkLoop() {
        char buffer[4096];
        sockaddr_in senderAddr;
        int senderLen = sizeof(senderAddr);
        SOCKET s = client.getSocket();

        LARGE_INTEGER frequency;
        QueryPerformanceFrequency(&frequency); 

        while (running) {
            int bytes = recvfrom(s, buffer, 4096, 0, (sockaddr*)&senderAddr, &senderLen);
            
            if (bytes > 0) {
                LARGE_INTEGER now;
                QueryPerformanceCounter(&now);

                FixMessage msg;
                if (bytes < 256) {
                    memcpy(msg.buffer, buffer, bytes);
                    msg.length = bytes;
                    msg.arrivalTime = now.QuadPart;
                    messageQueue.push(msg);
                }
            } 
            else {
                std::this_thread::sleep_for(std::chrono::microseconds(1));
            }
        }
    }
};