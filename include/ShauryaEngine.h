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
    // 1. The Components
    std::thread processorThread;
    std::thread networkThread;
    std::atomic<bool> running;
    NetworkClient client;
    LockFreeQueue<FixMessage, 1024> messageQueue; // Internal Queue

public:
    ShauryaEngine() : running(false) {}

    ~ShauryaEngine() {
        stop();
    }

    bool start(const std::string& ip, int port) {
        if (running) return false;
        running = true;

        // 2. Start Processor (Consumer)
        processorThread = std::thread(&ShauryaEngine::processorLoop, this);

        // 3. Connect to Multicast
        if (!client.joinMulticast(ip, port)) {
            std::cerr << "[C++] Failed to join multicast.\n";
            running = false;
            if (processorThread.joinable()) processorThread.join();
            return false;
        }

        // 4. Start Network Listener (Producer)
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
        return Stats::latencies.back(); // Returns most recent latency
    }

private:
    // --- The Consumer Thread ---
    void processorLoop() {
        FixMessage msg;
        while (running) {
            if (messageQueue.pop(msg)) {
                FixParser::parse(msg);
            } else {
                 std::this_thread::sleep_for(std::chrono::nanoseconds(100)); // Ultra-tight loop
            }
        }
    }

    // --- The Producer Thread (New!) ---
    void networkLoop() {
        char buffer[4096];
        sockaddr_in senderAddr;
        int senderLen = sizeof(senderAddr);
        SOCKET s = client.getSocket();

        LARGE_INTEGER frequency;
        QueryPerformanceFrequency(&frequency); // For timing

        while (running) {
            int bytes = recvfrom(s, buffer, 4096, 0, (sockaddr*)&senderAddr, &senderLen);
            
            if (bytes > 0) {
                // Timestamp Arrival (Zero-Latency Check)
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
                // Yield slightly to prevent 100% CPU usage on empty socket
                std::this_thread::sleep_for(std::chrono::microseconds(1));
            }
        }
    }
};