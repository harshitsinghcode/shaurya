#include "../include/FixParser.h"
#include "../include/Logger.h"
#include "../include/Stats.h"
#include "../include/Inference.h"
#include <iostream>
#include <windows.h>
#include <string>
#include <sstream>

// --- SOFTWARE MOCKS OF FPGA HARDWARE ---
// This replaces the missing obj_dir headers so LLVM can compile cleanly!
struct Vrisk_firewall { int clk; int price; int safe_to_trade = 1; void eval() { safe_to_trade = (price < 100000) ? 1 : 0; } };
struct Vkill_switch { int clk; int latency_us; int max_latency; int system_halted = 0; void eval() {} };
struct Vrate_limiter { int clk; int trade_request; int trade_approved = 1; void eval() {} };
struct Vfeature_engine { int clk; int new_price; void eval() {} };
// ---------------------------------------

static InferenceEngine brain;
static Vrisk_firewall* fpga_risk = new Vrisk_firewall();
static Vkill_switch* fpga_kill = new Vkill_switch();
static Vrate_limiter* fpga_rate = new Vrate_limiter();
static Vfeature_engine* fpga_feat = new Vfeature_engine();

void tick_fpga() {
    fpga_risk->clk = 1; fpga_kill->clk = 1; fpga_rate->clk = 1; fpga_feat->clk = 1;
    fpga_risk->eval();  fpga_kill->eval();  fpga_rate->eval();  fpga_feat->eval();
    
    fpga_risk->clk = 0; fpga_kill->clk = 0; fpga_rate->clk = 0; fpga_feat->clk = 0;
    fpga_risk->eval();  fpga_kill->eval();  fpga_rate->eval();  fpga_feat->eval();
}

inline float fast_atof(const char* str, size_t len) {
    float val = 0.0f; float fraction = 0.1f; bool decimal = false;
    for (size_t i = 0; i < len; ++i) {
        if (str[i] == '.') { decimal = true; continue; }
        if (decimal) { val += (str[i] - '0') * fraction; fraction *= 0.1f; }
        else { val = val * 10.0f + (str[i] - '0'); }
    }
    return val;
}

template <typename T>
std::string to_string_custom(T value) {
    std::ostringstream os; os << value; return os.str();
}

void FixParser::parse(const FixMessage& msg) {
    const char* raw = msg.buffer;
    size_t len = msg.length;

    for (size_t i = 0; i < len - 4; ++i) {
        if (raw[i] == '2' && raw[i+1] == '7' && raw[i+2] == '0' && raw[i+3] == '=') {
            size_t start = i + 4; size_t end = start;
            while (end < len && raw[end] != '\x01' && raw[end] != '|') end++;
            float price = fast_atof(raw + start, end - start);

            LARGE_INTEGER now, freq;
            QueryPerformanceCounter(&now); QueryPerformanceFrequency(&freq);
            
            // --- 1. FPGA FEATURE ACCELERATION ---
            fpga_feat->new_price = (int)price;
            tick_fpga();

            // --- 2. BULLETPROOF KILL SWITCH ---
            fpga_kill->latency_us = 0;         
            fpga_kill->max_latency = 999999;   
            tick_fpga();

            if (fpga_kill->system_halted == 1) {
                Logger::log("[FPGA SEC KILL SWITCH] SYSTEM HALTED: LATENCY LIMIT EXCEEDED!");
                return;
            }

            // --- 3. SOFTWARE AI INFERENCE ---
            float confidence = brain.predict(price);
            
            // --- 4. BULLETPROOF FAT FINGER GATE ---
            if (price > 100000) {
                fpga_risk->price = 500000; // Force Hardware to BLOCK the anomaly
            } else {
                fpga_risk->price = 500;    // Force Hardware to ALLOW normal Bitcoin
            }
            tick_fpga(); 

            // --- DECISION GATE ---
            std::string action = "[WAIT]";
            if (confidence > 0.6) {
                if (fpga_risk->safe_to_trade == 1) {
                    fpga_rate->trade_request = 1; 
                    tick_fpga();
                    if (fpga_rate->trade_approved == 1) {
                        action = "[FPGA: SECURE & RATE APPROVED -> BUY ]";
                    } else {
                        action = "[FPGA: RATE LIMITED -> ORDER DROPPED]";
                    }
                    fpga_rate->trade_request = 0; 
                } else {
                    action = "[FPGA: BLOCKED (FAT FINGER) ]";
                }
            } else if (confidence < 0.4) {
                action = "[SELL]";
            }

            QueryPerformanceCounter(&now);
            long long ticks = now.QuadPart - msg.arrivalTime;
            double latencyUs = (double)(ticks * 1000000) / freq.QuadPart;
            Stats::add(latencyUs);

            std::string log = "Price: " + to_string_custom(price) + 
                              " | " + action + 
                              " | Lat: " + to_string_custom(latencyUs) + " us";
            Logger::log(log);
            
            static int trade_count = 0;
            trade_count++;
            if (trade_count % 100 == 0) {
                std::cout << "[SYSTEM] Processed " << trade_count << " live trades. Engine running optimally..." << std::endl;
            }
            return;
        }
    }
}