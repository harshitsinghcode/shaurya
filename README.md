# ⚡SHAURYA v.0.2.0 - Scalable High-Frequency Architecture for Ultra-low Response Yield Access

![Language](https://img.shields.io/badge/language-C%2B%2B17-blue.svg)
![Latency](https://img.shields.io/badge/min%20latency-300%20ns-brightgreen.svg)
![Architecture](https://img.shields.io/badge/architecture-Lock--Free-orange.svg)
![Parsing](https://img.shields.io/badge/parsing-Zero--Copy-red.svg)
![Compiler](https://img.shields.io/badge/compiler-LLVM%2FClang-purple.svg)
![AI](https://img.shields.io/badge/AI-Zero%20Dependency%20Inference-teal.svg)
![Risk](https://img.shields.io/badge/risk-FPGA--Style%20Firewall-critical.svg)
![Pipeline](https://img.shields.io/badge/pipeline-88µs%20End--to--End-success.svg)
![Training](https://img.shields.io/badge/Training-Python-yellow.svg)
![Fusion](https://img.shields.io/badge/Compiler-LLVM%20Fusion-purple.svg)
![Execution](https://img.shields.io/badge/Execution-Vectorized%20CPU-brightgreen.svg)
![Inference](https://img.shields.io/badge/Inference-Eigen%20AI-orange.svg)
![Risk](https://img.shields.io/badge/Risk-FPGA%20Firewall-critical.svg)
![Networking](https://img.shields.io/badge/Networking-Lock--Free-red.svg)
---

## 🧠 Introduction

**Shaurya (`hft.shaurya`)** is an ultra-low latency heterogeneous high-frequency trading (HFT) framework that bridges Python-based AI model development with deterministic C++ execution performance.

Designed for:

- 📈 Quantitative Researchers  
- 🏢 Proprietary Trading Engineers  
- ⚙️ Systems Programmers  
- 🎓 HPC & Compiler Enthusiasts  

Shaurya enables **deep learning inference, hardware-style risk control, and lock-free networking** in a unified deterministic execution pipeline.

> ⚡ Full pipeline latency: ~88µs  
> (Network → FIX Parse → AI Inference → FPGA Risk → Routing)

---

## 📑 Table of Contents

- [Architecture Overview](#-architecture-overview)
- [Key Features](#-key-features)
- [Installation](#-installation)
- [Usage Guide](#usage-guide)
- [Technical Deep Dive](#-technical-deep-dive)
- [Performance Metrics](#-performance-metrics)
- [Configuration](#-configuration)
- [Examples](#-examples)
- [Troubleshooting](#-troubleshooting)
- [Roadmap](#-roadmap)

---

# 🧱 Architecture Overview

Python Training → Model Export → LLVM Fusion → Vectorized CPU Execution
│
├── Eigen AI Inference
├── FPGA Risk Firewall
└── Lock-Free Networking


Shaurya follows a **Heterogeneous Software-in-the-Loop (SIL)** architecture:

| Layer | Purpose |
|-------|----------|
| 🐍 Python | Train ML models (TensorFlow/Keras) |
| ⚙️ C++ | Deterministic inference execution |
| 🔌 RTL-style Risk | Hardware-like safety validation |
| 🔧 LLVM/Clang | Whole-program optimization + LTO fusion |

---

# 🚀 Key Features

## ✅ Deterministic AI Inference
- No Python runtime
- No GIL
- No garbage collection pauses
- Header-only inference
- Eigen-backed linear algebra

## ✅ FPGA-Style Risk Firewall
- Fat-finger protection
- Kill-switch logic
- Rate limiting
- Price-range validation
- Branchless logic design

## ✅ Lock-Free Networking
- SPSC ring buffer
- `std::atomic` synchronization
- Cache-line aligned memory (`alignas(64)`)
- Zero-copy FIX handling

## ✅ LLVM Fusion
- `-flto` Link-Time Optimization
- Cross-module inlining
- Dead code elimination
- `-march=native` AVX2 vectorization
- `-ffast-math` throughput optimization

---

# 📦 Installation

### 🛣️ Python Gateway

```bash
pip install hft.shaurya==0.2.0
```

`C++ Core Requires:`

1. LLVM/Clang
2. `lld linker`
3. C++17 compatible compiler

> Build using provided scripts:
```
clang++ -O3 -flto -march=native -ffast-math ...
```
`Then run:`
```
bin\Shaurya.exe
```
---

# 🔨Usage Guide

##  🕐 Step 1: Start Market Gateway
```
python -m hft.shaurya.gateway
```
or
```
python bridge.py
```
> The Python layer:

1. Aggregates exchange feeds

2. Streams FIX messages locally

3. Forwards data to C++ core

## 🕑 Step 2: Launch LLVM C++ Core

```
bin\Shaurya.exe
```
> Startup Process:

1. Loads AI weights
2. Warms CPU instruction cache
3. Initializes ring buffers
4. Begins live tick processing

## 🕒 Step 3 — Review Metrics

> After shutdown (Ctrl + C)
🌠 Shaurya_Metrics.txt includes:

1. Average latency
2. 99th percentile
3. Tail latency distribution
4. Message throughput

---

# 🔬 Technical Deep Dive

## 1️⃣ LLVM/Clang Infrastructure

> Shaurya prioritizes LLVM over GCC for:

- Whole-program analysis
- Cross-module inlining
- Vectorized math fusion
- Aggressive dead-code elimination

- Compiler flags used:
```
-flto
-march=native
-ffast-math
```

## 2️⃣ Deep Learning Alpha Engine

> Model Pipeline
```
.h5 (Keras)
   ↓
fdeep_model.json
   ↓
Header-only C++ inference
```

`Benefits:`

1. No Python interpreter
2. No runtime framework
3. Cache-friendly execution
4. Deterministic latency


## 3️⃣ Software-in-the-Loop FPGA Risk Engine

 ```
Traditional systems:

if(price > limit) { block(); }
```

## 🗺️ Shaurya approach:

1. Gate-style evaluation
2. Branchless evaluation trees
3. Avoids branch predictor penalties
4. Emulates RTL-style hardware logic

`Sample output:`
```
[FPGA: BLOCKED (FAT FINGER)]
```

## 4️⃣ Zero-Copy Lock-Free Pipeline

1. Single-producer single-consumer (SPSC)
2. Atomic pointer arithmetic
3. Cache-aligned buffers
4. No mutex locks
5. No scheduler interference

---

# 📊 Performance Metrics

## 💪🏻 Benchmark Method

- Windows `QueryPerformanceCounter`
- Full tick lifecycle measurement:
  - Network Buffer  
  - FIX Parse  
  - AI Inference  
  - FPGA Risk Gate  
  - Routing  

## ✅ Results

| Metric              | Value     |
|---------------------|----------|
| Messages Tested     | 1000+    |
| Minimum Latency     | 3.6 µs   |
| Average Latency     | 88.38 µs |
| 99th Percentile     | 237.0 µs |

> 99% of trades complete in under **0.25 milliseconds**, even under OS scheduler load.

---

# 🔩 Configuration 

> Key Optimization Flags

```bash
-O3
-flto
-march=native
-ffast-math
```

🍁 Recommended System Tuning

- Disable power-saving modes  
- Pin threads to dedicated CPU cores  
- Use performance CPU governor (Linux)  
- Disable unnecessary background processes  

---

# 💡 Examples

> Running a Trained Model

1. Train model in Python  
2. Export `.h5`  
3. Convert to `fdeep_model.json`  
4. Place model in inference directory  
5. Launch core engine  

---

> Risk Rule Example

```cpp
RiskGate fatFinger( max_notional = 1'000'000 );
RiskGate priceClamp( max_slippage = 0.5% );
```

---


# 🎯 Who Benefits?

## 📈 Retail & Quant Traders

- AI-driven live execution  
- Sub-millisecond architecture  
- Institutional-grade safety  

## 🏢 Proprietary Firms

- Rapid FPGA prototyping (SIL)  
- Deterministic backtesting  
- Infrastructure experimentation  

## 🎓 Computer Science Students

Real-world examples of:

- Lock-free systems  
- LLVM optimization  
- Vectorized math  
- HPC finance pipelines  

---

# 🚀 Roadmap

- [ ] GPU kernel fusion experiments  
- [ ] Native FPGA backend  
- [ ] Linux ultra-low-latency build  
- [ ] Advanced order routing simulator  
- [ ] Real exchange connectivity modules  

---

# 🧪 Troubleshooting

## 📈 High Latency Spikes

- Verify CPU scaling disabled  
- Ensure LTO enabled  
- Confirm AVX2 available  

## 🙅🏻‍♀️ Model Not Loading

- Validate `fdeep_model.json`  
- Ensure correct path  
- Check weight precision compatibility  

## 🏢 Build Issues

- Confirm Clang version compatibility  
- Ensure `lld` installed  
- Rebuild with verbose logging  

---

# ☢️ Disclaimer

> Shaurya is intended for:

- Research  
- Education  
- Systems experimentation  

`It is not financial advice and not production-certified trading infrastructure.`

> Users assume full responsibility for:

- Trading decisions  
- Compliance  
- Regulatory adherence  
- Capital risk  

---

# 🏁 Final Note

The engine is solely contributed by Harshit Kumar Singh, me(;

Shaurya v.0.2.0 represents a shift toward democratized institutional-grade infrastructure : merging AI, compiler engineering, and hardware-style safety into a single deterministic execution engine.
>If this project helps you, consider ⭐ starring the repository and contributing to future releases and till then happy coding 😊.

`ad astra per aspera 🛩️`
