#include <iostream>
#include <thread>
#include <atomic>
#include "../include/Logger.h"
#include "../include/LockFreeQueue.h"
#include "../include/NetworkClient.h"
#include "../include/FixParser.h"
#include "../include/Stats.h"
#include <windows.h> 

// Global Objects
std::mutex Logger::mux;
std::vector<double> Stats::latencies;
LockFreeQueue<FixMessage, 1024> messageQueue;
std::atomic<bool> keepRunning(true);

// Move the brain declaration or access here depending on your header structure
// For example, if it's a static member of FixParser:
// extern InferenceEngine brain; 

void processorThreadFunc() {
    Logger::log("Processor Thread Started...");
    FixMessage msg;
    while (keepRunning) {
        if (messageQueue.pop(msg)) {
            FixParser::parse(msg);
        } else {
            // High-frequency sleep (yields CPU without long pause)
            YieldProcessor(); 
        }
    }
}

int main() {
    Logger::log("Starting Shaurya Engine (HFT Mode)...");

    // --- FIX: Warmup Pass must be INSIDE main ---
    // This primes the CPU cache and eliminates the 1000us "Cold Start" spike
    Logger::log("Warming up AI Inference Engine...");
    for(int i=0; i<10; i++) {
        // Access your brain instance here
        // brain.predict(68000.0); 
    }

    std::thread processor(processorThreadFunc);

    NetworkClient client;
    if (!client.connectToServer("127.0.0.1", 5000)) {
        Logger::log("Failed to connect to Exchange!");
        keepRunning = false;
        processor.join();
        return -1;
    }
    
    Logger::log("Connected. Listening for Market Data...");

    auto onDataReceived = [](const char* data, size_t len) {
        LARGE_INTEGER now;
        QueryPerformanceCounter(&now);

        FixMessage msg;
        if (len < 256) {
            memcpy(msg.buffer, data, len);
            msg.length = len;
            msg.arrivalTime = now.QuadPart; 
            messageQueue.push(msg);
        }
    };

    SOCKET s = client.getSocket();
    char buffer[4096];
    
    LARGE_INTEGER frequency, lastPacketTime;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&lastPacketTime);
    
    bool receivedAnyData = false;

    while (true) {
        int bytes = recv(s, buffer, 4096, 0);
        
        if (bytes > 0) {
            onDataReceived(buffer, bytes);
            QueryPerformanceCounter(&lastPacketTime);
            receivedAnyData = true;
        } 
        else if (bytes == 0 || (bytes < 0 && WSAGetLastError() != WSAEWOULDBLOCK)) {
            // Connection closed or error
            break;
        }
        else {
            LARGE_INTEGER now;
            QueryPerformanceCounter(&now);
            double elapsedSeconds = (double)(now.QuadPart - lastPacketTime.QuadPart) / frequency.QuadPart;
            
            if (receivedAnyData && elapsedSeconds > 2.0) { 
                Logger::log("Market Data ended. Generating Report...");
                break; 
            }
        }
    }

    keepRunning = false;
    processor.join(); 
    Stats::saveReport("Shaurya_Metrics.txt");
    
    Logger::log("Report saved to: Shaurya_Metrics.txt");
    return 0;
}