#include <pybind11/pybind11.h>
#include <thread>
#include <chrono>

#include "ShauryaEngine.h" 
#include "Logger.h"
#include "Stats.h"

std::mutex Logger::mux;
std::vector<double> Stats::latencies;

namespace py = pybind11;

class PyShaurya {
    ShauryaEngine engine;
public:
    void start(std::string ip, int port) {
        engine.start(ip, port);
    }
    
    double get_latency() {
        return engine.getMinLatency();
    }

    void stop() {
        engine.stop();
    }

    void run_backtest(std::string file) {
        py::gil_scoped_release release; 
    }
};

PYBIND11_MODULE(shaurya_hft, m) {
    m.doc() = "Shaurya Ultra-Low Latency Engine";

    py::class_<PyShaurya>(m, "Engine")
        .def(py::init<>())
        .def("start", &PyShaurya::start, "Start the HFT Engine connection")
        .def("stop", &PyShaurya::stop, "Stop the Engine")
        .def("get_latency", &PyShaurya::get_latency, "Get minimum recorded latency");
        .def("run_backtest", &PyShaurya::run_backtest);
}