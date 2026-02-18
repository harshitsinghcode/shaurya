#pragma once
#include <iostream>
#include <mutex>
#include <string>

class Logger {
public:
    static std::mutex mux; 

    static void log(const std::string& msg) {
        std::lock_guard<std::mutex> lock(mux);
        // std::cout << "[shaurya] " << msg << std::endl;
    }
};