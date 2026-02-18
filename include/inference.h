#pragma once
#include <vector>
#include <iostream>
#include <deque>
#include "../frugally-deep/include/fdeep/fdeep.hpp"

class InferenceEngine {
    fdeep::model* model = nullptr;
    bool ready = false;
    std::deque<float> history;

public:
    InferenceEngine() {
        try {
            static const auto loaded_model = fdeep::load_model("shaurya_brain.json");
            model = new fdeep::model(loaded_model);
            ready = true;
            std::cout << "[AI] Neural Network Loaded Successfully.\n";
        } catch (const std::exception& e) {
            std::cerr << "[AI] ERROR: " << e.what() << "\n";
            ready = false;
        }
    }

    float predict(float current_price) {
        if (!ready) return 0.5f;

        history.push_back(current_price);
        if (history.size() > 4) history.pop_front();
        if (history.size() < 4) return 0.5f; 

        float d1 = history[1] - history[0];
        float d2 = history[2] - history[1];
        float d3 = history[3] - history[2];

        fdeep::tensor input_tensor(
            fdeep::tensor_shape(3), 
            std::vector<float>{d1, d2, d3}
        );

        const auto result = model->predict({input_tensor});
        return result.front().to_vector()[0];
    }
};