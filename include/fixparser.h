#pragma once
#include <vector>
#include <cstring>
#include <string>

struct StringViewLite {
    const char* data;
    size_t len;
    StringViewLite(const char* d, size_t l) : data(d), len(l) {}
    std::string toString() const { return std::string(data, len); }
};

struct FixMessage {
    char buffer[256];
    size_t length;
    long long arrivalTime;
};

class FixParser {
public:
    static void parse(const FixMessage& msg);
};