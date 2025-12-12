#include "../include/FixParser.h"
#include "../include/Logger.h"
#include "../include/Stats.h"
#include <iostream>
#include <windows.h> 
#include <string>
#include <sstream> 

template <typename T>
std::string to_string_custom(T value) {
    std::ostringstream os;
    os << value;
    return os.str();
}

void FixParser::parse(const FixMessage& msg) {
    const char* raw = msg.buffer;
    size_t len = msg.length;

    for (size_t i = 0; i < len - 4; ++i) {
        if (raw[i] == '2' && raw[i+1] == '7' && raw[i+2] == '0' && raw[i+3] == '=') {
            
            size_t start = i + 4;
            size_t end = start;
            while (end < len && raw[end] != '\x01' && raw[end] != '|') {
                end++;
            }
            
            StringViewLite priceView(raw + start, end - start);

            LARGE_INTEGER now, freq;
            QueryPerformanceCounter(&now);
            QueryPerformanceFrequency(&freq); 

            long long ticks = now.QuadPart - msg.arrivalTime;
            double latencyUs = (double)(ticks * 1000000) / freq.QuadPart;

            if (latencyUs < 0.01) latencyUs = 0.1;

            Stats::add(latencyUs);
            
            std::string logMsg = "Price: " + priceView.toString() + 
                                 " | Latency: " + to_string_custom(latencyUs) + " us";
            Logger::log(logMsg);
            
            return;
        }
    }
}