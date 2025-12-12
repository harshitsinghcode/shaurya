#pragma once
#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

class Stats {
public:
    static std::vector<double> latencies;
    static void add(double microseconds) {
        latencies.push_back(microseconds);
    }

    static void saveReport(const std::string& filename) {
        if (latencies.empty()) {
            std::cout << "[Shaurya] No data collected.\n";
            return;
        }

        std::sort(latencies.begin(), latencies.end());

        double minLat = latencies.front();
        double maxLat = latencies.back();
        double sum = std::accumulate(latencies.begin(), latencies.end(), 0.0);
        double avg = sum / latencies.size();
        size_t p99Index = (size_t)(latencies.size() * 0.99);
        double p99 = latencies[p99Index];

        std::cout << "\n========================================\n";
        std::cout << "       PERFORMANCE REPORT (SHAURYA)     \n";
        std::cout << "========================================\n";
        std::cout << "Total Messages : " << latencies.size() << "\n";
        std::cout << "Min Latency    : " << minLat << " us\n";
        std::cout << "Max Latency    : " << maxLat << " us\n";
        std::cout << "Avg Latency    : " << avg << " us\n";
        std::cout << "99th Percentile: " << p99 << " us  <-- CRITICAL\n";
        std::cout << "========================================\n";

        std::ofstream file(filename.c_str());
        file << "SHAURYA HFT ENGINE - LATENCY REPORT\n";
        file << "-----------------------------------\n";
        file << "Total Messages : " << latencies.size() << "\n";
        file << "Avg Latency    : " << avg << " us\n";
        file << "Max Latency    : " << maxLat << " us\n";
        file << "P99 Latency    : " << p99 << " us\n\n";
        file << "--- Raw Data (Microseconds) ---\n";
        for (size_t i = 0; i < latencies.size(); ++i) {
             file << latencies[i] << "\n";
        }
        file.close();
        std::cout << "[Shaurya] Report saved to: " << filename << "\n";
    }
};