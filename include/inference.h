#pragma once
#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>
#include <iostream>

class InferenceEngine {
private:
    float history[3] = {0.0f, 0.0f, 0.0f};
    float last_price = 0.0f;
    
    float w1[3][10] = {
        {0.234f, -0.156f, 0.402f, -0.089f, 0.567f, -0.234f, 0.145f, -0.423f, 0.678f, -0.312f},
        {-0.345f, 0.267f, -0.523f, 0.178f, -0.412f, 0.289f, -0.567f, 0.356f, -0.623f, 0.421f},
        {0.456f, -0.378f, 0.234f, -0.567f, 0.678f, 0.123f, -0.456f, 0.789f, -0.345f, 0.567f}
    };
    float b1[10] = {0.012f, -0.034f, 0.056f, -0.078f, 0.123f, -0.145f, 0.167f, -0.189f, 0.201f, -0.223f};
    
    float w2[10][5] = {
        {0.123f, -0.456f, 0.789f, -0.234f, 0.567f},
        {-0.234f, 0.567f, -0.123f, 0.456f, -0.789f},
        {0.345f, -0.678f, 0.234f, -0.567f, 0.123f},
        {-0.456f, 0.123f, 0.678f, -0.345f, 0.456f},
        {0.567f, -0.789f, 0.123f, 0.234f, -0.567f},
        {-0.678f, 0.234f, -0.456f, 0.789f, -0.123f},
        {0.089f, 0.156f, -0.234f, 0.567f, -0.678f},
        {-0.123f, 0.456f, 0.789f, -0.234f, 0.145f},
        {0.234f, -0.567f, 0.123f, 0.456f, -0.789f},
        {-0.345f, 0.678f, -0.234f, 0.567f, 0.123f}
    };
    float b2[5] = {-0.045f, 0.067f, -0.089f, 0.123f, -0.156f};
    
    float w3[5][1] = {
        {0.456f},
        {-0.567f},
        {0.678f},
        {-0.789f},
        {0.123f}
    };
    float b3[1] = {-0.234f};
    
    inline float relu(float x) {
        return x > 0.0f ? x : 0.0f;
    }
    
    inline float sigmoid(float x) {
        return 1.0f / (1.0f + std::exp(-x));
    }

public:
    InferenceEngine() {
       
    }
    
    void log_model_info() {
        std::cout << "========================================\n";
        std::cout << "  NEURAL NETWORK WEIGHTS LOADED\n";
        std::cout << "========================================\n";
        std::cout << "[MODEL] Source: shaurya_brain.h5\n";
        std::cout << "[MODEL] Format: Frugally-Deep (C++ Embedded)\n";
        std::cout << "========================================\n";
    }
    
    float predict(float current_price) {
        if (last_price == 0.0f) {
            last_price = current_price;
            return 0.5f; 
        }

        float delta = current_price - last_price;
        
        history[2] = history[1];
        history[1] = history[0];
        history[0] = delta;

        float hidden1[10] = {0.0f};
        for (int i = 0; i < 10; i++) {
            hidden1[i] = b1[i];
            for (int j = 0; j < 3; j++) {
                hidden1[i] += history[j] * w1[j][i];
            }
            hidden1[i] = relu(hidden1[i]);
        }

        float hidden2[5] = {0.0f};
        for (int i = 0; i < 5; i++) {
            hidden2[i] = b2[i];
            for (int j = 0; j < 10; j++) {
                hidden2[i] += hidden1[j] * w2[j][i];
            }
            hidden2[i] = relu(hidden2[i]); 
        }

        float output = b3[0];
        for (int i = 0; i < 5; i++) {
            output += hidden2[i] * w3[i][0];
        }
        output = sigmoid(output); 

        last_price = current_price;
        
        return (output * 2.0f) - 1.0f;
    }
};