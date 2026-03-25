#include "../include/FixParser.h"
#include "../include/Logger.h"
#include "../include/Stats.h"
#include "../include/Inference.h" // <--- 1. INCLUDE THE BRAIN
#include <iostream>
#include <windows.h> 
#include <string>
#include <sstream> 
#include <iomanip>

// 2. INSTANTIATE THE BRAIN (Static so it persists between function calls)
static InferenceEngine brain;

// Flag to track first initialization
static bool ai_initialized = false; 

// Helper: Extremely fast string-to-float for HFT (Zero Allocations)
// Much faster than std::stof
inline float fast_atof(const char* str, size_t len) {
    float val = 0.0f;
    float fraction = 0.1f;
    bool decimal = false;

    for (size_t i = 0; i < len; ++i) {
        if (str[i] == '.') {
            decimal = true;
            continue;
        }
        if (decimal) {
            val += (str[i] - '0') * fraction;
            fraction *= 0.1f;
        } else {
            val = val * 10.0f + (str[i] - '0');
        }
    }
    return val;
}

// Helper to stringify numbers
template <typename T>
std::string to_string_custom(T value) {
    std::ostringstream os;
    os << value;
    return os.str();
}

void FixParser::parse(const FixMessage& msg) {
    const char* raw = msg.buffer;
    size_t len = msg.length;
    
    // Scan for "270=" (FIX Tag for Price)
    for (size_t i = 0; i < len - 4; ++i) {
        if (raw[i] == '2' && raw[i+1] == '7' && raw[i+2] == '0' && raw[i+3] == '=') { 
            size_t start = i + 4;
            size_t end = start;
            // Find end of the value (delimiter is usually SOH or |)
            while (end < len && raw[end] != '\x01' && raw[end] != '|') {
                end++;
            }
            
            // 3. FAST PARSE (Zero Copy - Convert in place)
            float current_price = fast_atof(raw + start, end - start);

            // ---------------------------------------------------------
            // 4. >>> THE AI INFERENCE LOOP <<<
            // This runs the trained 3-layer neural network (10->5->1 neurons)
            // Takes 3 price deltas as input, outputs probability [0, 1] scaled to [-1, 1]
            float ai_signal = brain.predict(current_price);
            
            // Scale back to raw probability for reporting
            float ai_probability = (ai_signal + 1.0f) / 2.0f; // Convert from [-1, 1] to [0, 1]
            
            // Log once that AI is initialized
            if (!ai_initialized) {
                std::cout << "\n";
                brain.log_model_info();  // Print weight info on first tick
                std::cout << "[SYSTEM] AI Neural Network inference ACTIVE\n\n";
                ai_initialized = true;
            }
            // ---------------------------------------------------------

            // 5. LATENCY TRACKING
            LARGE_INTEGER now, freq;
            QueryPerformanceCounter(&now);
            QueryPerformanceFrequency(&freq); 
            long long ticks = now.QuadPart - msg.arrivalTime;
            double latencyUs = (double)(ticks * 1000000) / freq.QuadPart;
            if (latencyUs < 0.01) latencyUs = 0.1; // Clamp min latency
            Stats::add(latencyUs);

            // 6. DECISION LOGIC
            std::string action = "";
            std::string confidence = "";
            if (ai_signal > 0.6f) {
                action = " [>>> BUY <<<]";
                confidence = "STRONG BUY (AI: " + to_string_custom(ai_probability * 100.0f) + "%)";
            }
            else if (ai_signal < -0.6f) {
                action = " [<<< SELL >>>]";
                confidence = "STRONG SELL (AI: " + to_string_custom((1.0f - ai_probability) * 100.0f) + "%)";
            }
            else {
                action = " [HOLD]";
                confidence = "NEUTRAL (AI: " + to_string_custom(ai_probability * 100.0f) + "%)";
            }

            // 7. LOG OUTPUT
            // Shows Price, AI Confidence Score, Action, and Speed
            std::string logMsg = "Price: " + to_string_custom(current_price) + 
                                 " | " + confidence +
                                 action + 
                                 " | Lat: " + to_string_custom(latencyUs) + " us";
            
            Logger::log(logMsg);
            return;
        }
    }
}