# ⚔️ SHAURYA v0.3.2: Scalable High-Frequency Architecture for Ultra-Low Response Yield Access
> *A heterogeneous Software-in-the-Loop (SIL) execution engine that resolves the HFT trilemma — ultra-low latency, deterministic risk management, and deep learning inference — through compiler-driven fusion on commodity hardware.*

---
![Language](https://img.shields.io/badge/Language-C%2B%2B20-blue.svg)
![Standard](https://img.shields.io/badge/Standard-C%2B%2B20-blue.svg)
![Python](https://img.shields.io/badge/Python-3.10%2B-yellow.svg)
![Compiler](https://img.shields.io/badge/Compiler-LLVM%2FClang-purple.svg)
![LTO](https://img.shields.io/badge/Optimization-LTO-purple.svg)
![SIMD](https://img.shields.io/badge/SIMD-AVX2%2FAVX--512-orange.svg)
![Vectorization](https://img.shields.io/badge/Vectorization-AVX2-brightgreen.svg)
![Min Latency](https://img.shields.io/badge/Min%20Latency-1.75%20%C2%B5s-brightgreen.svg)
![Avg Latency](https://img.shields.io/badge/Avg%20Latency-4.22%20%C2%B5s-brightgreen.svg)
![P99 Latency](https://img.shields.io/badge/99th%20Percentile-40.9%20%C2%B5s-yellow.svg)
![AI Inference](https://img.shields.io/badge/AI%20Inference-%3C1.2%20%C2%B5s-blue.svg)
![Risk Validation](https://img.shields.io/badge/Risk%20Validation-%3C0.5%20%C2%B5s-critical.svg)
![Throughput](https://img.shields.io/badge/Throughput-237k%20msgs%2Fs-success.svg)
![Speedup](https://img.shields.io/badge/Speedup-81x%20vs%20Naive-red.svg)
![Architecture](https://img.shields.io/badge/Architecture-Software--in--the--Loop%20(SIL)-blueviolet.svg)
![Determinism](https://img.shields.io/badge/Determinism-Bounded%20Tail-success.svg)
![Lock-Free](https://img.shields.io/badge/Concurrency-Lock--Free-red.svg)
![SPSC](https://img.shields.io/badge/Queue-SPSC%20Ring%20Buffer-orange.svg)
![False Sharing](https://img.shields.io/badge/False%20Sharing-Prevented%20(alignas%2064)-brightgreen.svg)
![Zero-Copy](https://img.shields.io/badge/Networking-Zero--Copy%20FIX%20Parser-blue.svg)
![Branchless](https://img.shields.io/badge/Risk%20Logic-Branchless%20Bitwise-critical.svg)
![RTL](https://img.shields.io/badge/Risk%20Model-RTL--in--Software-red.svg)
![AI Framework](https://img.shields.io/badge/Training-Keras%2FTensorFlow-yellow.svg)
![Inference Engine](https://img.shields.io/badge/Inference-Eigen%20%2B%20frugally--deep-teal.svg)
![Model Format](https://img.shields.io/badge/Model%20Format-Static%20JSON-blue.svg)
![No GIL](https://img.shields.io/badge/Python%20GIL-Eliminated%20from%20Critical%20Path-brightgreen.svg)
![No GC](https://img.shields.io/badge/Garbage%20Collection-None%20in%20Hot%20Path-success.svg)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-lightgrey.svg)
![Windows](https://img.shields.io/badge/Windows-Bare%20Metal-blue.svg)
![Linux](https://img.shields.io/badge/Linux-AWS%20EC2%20(Ubuntu)-orange.svg)
![Cloud](https://img.shields.io/badge/Cloud-AWS%20Nitro%20Hypervisor-critical.svg)
![Cross-Platform](https://img.shields.io/badge/Cross--Platform-POSIX%20%2F%20WinSock2-blue.svg)
![Real-Time Priority](https://img.shields.io/badge/Scheduling-Real--Time%20Priority-success.svg)
![X11](https://img.shields.io/badge/Dashboard-X11%20Forwarding%20%2F%20Headless-yellow.svg)
![PyPI](https://img.shields.io/pypi/v/hft.shaurya?label=PyPI&color=blue)
![PyPI Downloads](https://img.shields.io/pypi/dm/hft.shaurya?label=Downloads&color=blue)
![GitHub Stars](https://img.shields.io/github/stars/harshitsinghcode/shaurya?style=social)
![GitHub Release](https://img.shields.io/github/v/release/harshitsinghcode/shaurya)
![Code Size](https://img.shields.io/github/languages/code-size/harshitsinghcode/shaurya)

## 🧠 Introduction

**SHAURYA** (`hft.shaurya`) is an ultra-low latency, LLVM-optimized C++20 High-Frequency Trading (HFT) framework that bridges Python-based AI model development with deterministic bare-metal execution performance. It is a **heterogeneous Software-in-the-Loop (SIL)** system, meaning the entire pipeline — from live market data ingestion to order routing — is treated as a **single unified computational graph** and optimized statically at compile time via LLVM/Clang's Link-Time Optimization (LTO) and AVX2 SIMD vectorization.

Unlike traditional approaches that force a choice between FPGA rigidity and software jitter, SHAURYA occupies a unique middle ground: the flexibility and iteration speed of high-level language development (Python/Keras), fused with the determinism and throughput of bare-metal C++ execution.

**Designed for:**
- 📈 Quantitative Researchers
- 🏢 Proprietary Trading Engineers
- ⚙️ Systems & Compiler Enthusiasts
- 🎓 HPC & Finance Students

---

## 🏗️ Architecture Overview

SHAURYA's execution pipeline is built on five tightly integrated layers, each engineered to eliminate non-determinism at the specific abstraction level it targets:

<p align="center">
  <img src="https://github.com/user-attachments/assets/140c6827-20a1-406e-ba46-c9dee09428df" width="900"/>
</p>

**Compile-time optimization stack:**

```
Source C++20
    └─ LLVM/Clang
        ├─ -flto         → Link-Time Optimization (whole-program inlining, DCE)
        ├─ -march=native → AVX2/AVX-512 SIMD vectorization
        ├─ -O3           → Aggressive loop unrolling, constant folding
        └─ -ffast-math   → Fused multiply-add, relaxed IEEE754 for throughput
```

**Layer mapping:**

| Layer | Language | Role |
|---|---|---|
| Data Gateway | Python (async) | Live FIX feed ingestion, GIL-isolated |
| Execution Core | C++20 (bare-metal) | Zero-copy parsing, AI inference, risk validation |
| Risk Firewall | RTL-in-C++ (Verilog-like) | Branchless hardware-grade safety gates |
| Compiler Toolchain | LLVM/Clang + lld | LTO, SIMD fusion, cross-module inlining |
| Telemetry | Python Tkinter | Detached process, no critical path impact |

---

## ⚡ Performance

Benchmarked over a 50-stock basket (1,000 ticks) across two deployment environments:

**Bare-Metal (Windows 11, Intel i7-12700K @ 4.9 GHz, 32 GB DDR4-3600):**

| Metric | Value |
|---|---|
| Minimum End-to-End Latency | **1.75 µs** |
| Mean Pipeline Latency | **4.22 µs** |
| 90th Percentile | 6.3 µs |
| 99th Percentile | 40.9 µs |
| Peak (OS DPC spike) | 127 µs |
| Speedup vs. Naïve Baseline | **81x** |

**AWS EC2 (c6i.large, Ubuntu 22.04, Nitro Hypervisor):**

| Metric | Value |
|---|---|
| Minimum Latency | 2.09 µs |
| Mean Latency | 36.77 µs |
| 90th Percentile | 52.3 µs |
| 99th Percentile | 118 µs |
| Hypervisor Tax (socket stage) | ~31.6 µs |

**Pipeline stage breakdown (bare-metal vs. cloud):**

| Stage | Bare Metal | AWS |
|---|---|---|
| Socket receive | 0.8 µs | 32.4 µs |
| FIX parsing + AI inference | 3.1 µs | 3.8 µs |
| Risk validation | 0.3 µs | 0.4 µs |

The socket receive stage accounts for **>97% of the hypervisor overhead** — the C++ execution core itself scales near-identically between environments. Static AI compilation alone provides a **20× latency penalty** when replaced with TensorFlow's dynamic runtime.

---

## 🚀 Key Features

### ✅ Zero-Copy FIX Parser

Traditional FIX parsers construct `std::string` objects and call `std::stof` for numeric conversion — both involve heap allocation with non-deterministic latency due to memory fragmentation and locale-dependent formatting. SHAURYA's parser operates directly on the raw socket receive buffer using:

- **Strict pointer arithmetic** to identify FIX tag delimiters (SOH, `0x01`) without copying
- **Branchless finite state machine** (`WAITING_FOR_TAG → READING_TAG → READING_VALUE`) with states chosen to maximize branch predictor hit rate
- **`fast_atof` implementation** — a custom ASCII-to-float converter using pre-computed power-of-ten divisors and integer arithmetic, bypassing locale lookups and exception paths entirely
- **POD struct output** with `alignas(64)` cache-line alignment for immediate L1 access by the downstream ring buffer

Total parsing time for a 200-byte FIX message: **< 500 ns** on bare metal.

### ✅ Lock-Free SPSC Ring Buffer

The inter-thread data transport uses a Single-Producer Single-Consumer (SPSC) lock-free ring buffer — a pre-allocated fixed-size circular array that never allocates memory during operation.

Key micro-architectural details:
- **`std::memory_order_release`** on producer commit index writes — establishes a happens-before relationship without sequential consistency overhead
- **`std::memory_order_acquire`** on consumer commit index reads — pairs with release semantics to synchronize without a full memory fence
- **56-byte padding** between producer and consumer indices (or `alignas(64)` placement in separate structs) — eliminates **false sharing**, the phenomenon where independent cache-line writes by different CPU cores trigger MESI protocol invalidations, causing expensive L1 cache flushes on the peer thread
- **Bitwise wrap-around** (`index & (capacity - 1)` where capacity is a power of two) — avoids modulo division in the hot loop

Throughput: **> 50 million messages/second** on a single core. Push/pop latency: **< 20 ns** when buffer is not full.

### ✅ Static Deep Learning Alpha Engine

Conventional inference frameworks (TensorFlow, PyTorch) use dynamic computational graphs, heap-allocated tensor objects, and garbage-collected runtimes — all sources of non-deterministic latency on the order of tens to hundreds of microseconds, making them incompatible with any sub-100 µs HFT pipeline.

SHAURYA's approach:

**1. Offline training (Python/Keras):**
A feed-forward neural network (input: 20 lagged mid-prices → hidden: 128 ReLU → hidden: 64 ReLU → output: buy/sell/hold signal) is trained offline with TensorFlow. Architecture is intentionally overparameterized to stress-test the inference engine.

**2. Static export via frugally-deep:**
The trained `.h5` model is converted to `fdeep_model.json` — a human-readable JSON file containing the full network topology, weight matrices (as flat float arrays), and bias vectors, with zero Python runtime dependencies.

**3. Header-only C++ inference (Eigen + frugally-deep):**
At engine startup, the JSON is parsed once by the frugally-deep header-only library, which pre-allocates all tensors. The computational graph is then mapped to the **Eigen C++ linear algebra library**, which uses **expression templates** for lazy evaluation — avoiding temporary allocations — and emits **AVX2-vectorized BLAS kernels** for matrix multiplications.

**4. Compile-time optimization by LLVM:**
Since the network architecture is fully known at compile time, LLVM/Clang performs:
- **Loop unrolling** across all layer computations
- **Cross-translation-unit inlining** (via LTO) of all Eigen expression templates
- **Branchless ReLU** via bitwise masking: `x & (x > 0)` — no branch misprediction penalty
- **FMA (Fused Multiply-Add) fusion** — bias addition merged into the matrix multiply kernel to minimize memory traffic

AI inference latency: **< 1.2 µs** on bare metal. **Zero Python GIL. Zero TensorFlow runtime. Zero garbage collection.**

### ✅ Simulated FPGA RTL Risk Firewall

Regulatory frameworks (MiFID II, SEC Rule 15c3-5) mandate unconditional pre-trade risk controls: kill switches, price clamps, fat-finger protection, and rate limiters. Hardware FPGA implementations guarantee nanosecond-level determinism but are inflexible and expensive to modify. Traditional software `if-else` chains are vulnerable to **branch misprediction** — when the CPU speculatively executes the wrong branch and must flush and refill the pipeline (10–20 cycle penalty per misprediction).

SHAURYA implements a **Register-Transfer Level (RTL)-in-software** firewall: all risk rules are expressed as **branchless bitwise operations and arithmetic masking**, directly analogous to combinational logic gates in hardware.

Example evaluations:
```cpp
// Price clamp (no branch)
uint32_t valid = (price < max_price) & (price > min_price);

// Kill switch (no branch)
allow = allow & (!kill_signal);

// Fat-finger protection
uint32_t notional_ok = (quantity * price) < max_notional;
```

The entire risk evaluation tree — covering price clamps, rate limits, position limits, and kill switches — is transpiled from Verilog-like hardware description at compile time into a single, cache-aligned C++ evaluation sequence. It resides in the **L1 instruction cache** throughout execution. Deterministic risk validation latency: **< 0.5 µs per evaluation**, with zero variance from branch misprediction.

### ✅ LLVM/Clang Compiler Infrastructure

SHAURYA exclusively targets LLVM/Clang (not GCC) for the following reasons:

- **Intermediate Representation (IR):** LLVM operates on a well-defined SSA-form IR, enabling optimization passes that are impossible at the source level
- **Link-Time Optimization (LTO) via libLTO:** Bitcode from all translation units is merged at link time, allowing the compiler to perform whole-program analysis — dead code elimination, cross-module inlining, and loop transformations across what would otherwise be opaque ABI boundaries
- **`-march=native`:** Generates code targeting the exact CPU microarchitecture of the build machine, enabling AVX2/AVX-512 packed floating-point instructions
- **`-ffast-math`:** Enables reassociation, contraction (FMA), and reciprocal approximations — safe for HFT workloads where IEEE 754 strict compliance is not required
- **`lld` linker:** LLVM's native linker, significantly faster than GNU `ld` for LTO workloads

### ✅ Cross-Platform Deployment

SHAURYA targets both **Windows 11 bare-metal** and **Linux (AWS EC2 Ubuntu)** from a single codebase. All OS-specific syscalls are wrapped in preprocessor directives:

| Feature | Windows | Linux |
|---|---|---|
| Sockets | `WinSock2` / `SOCKET` | POSIX / `int fd` |
| Thread affinity | `SetThreadAffinityMask` | `pthread_setaffinity_np` |
| Real-time scheduling | `REALTIME_PRIORITY_CLASS` | `SCHED_FIFO`, priority 99 |
| High-res timer | `QueryPerformanceCounter` | `clock_gettime(CLOCK_MONOTONIC)` |
| Socket close | `closesocket()` | `close()` |

### ✅ Telemetry & Observation Plane

The dashboard runs as a **completely separate OS process**, communicating with the C++ engine via a **named pipe or local UDP socket**. This decoupling is critical — GUI rendering can take several milliseconds and must never block the execution thread.

Features:
- Real-time latency histograms and 99th percentile tail display
- Risk violation counters and firewall gate status
- **Headless mode** for cloud deployments: writes PNG chart output, compatible with X11 forwarding via `ssh -X`
- Per-run metrics file (`SHAURYA_Metrics.txt`) with per-tick latency records for post-hoc statistical analysis

---

## 📦 Installation

### Python Gateway

```bash
pip install hft.shaurya==0.3.0
```

### C++ Core — Prerequisites

- LLVM/Clang (≥ 14 recommended)
- `lld` linker
- C++17/C++20 compatible compiler
- Eigen (header-only, bundled)
- frugally-deep (header-only, bundled)

### Build

```bash
# Windows
clang++ -O3 -flto -march=native -ffast-math -std=c++20 \
    -fuse-ld=lld src/*.cpp -o bin/Shaurya.exe

# Linux
clang++ -O3 -flto -march=native -ffast-math -std=c++20 \
    -fuse-ld=lld src/*.cpp -o bin/Shaurya -lpthread -lnuma
```

---

## 🔨 Usage

### Step 1 — Start Market Gateway

```bash
python gateway.py
# or
python -m hft.shaurya.gateway
```

The Python layer connects to a live data feed (e.g., Yahoo Finance), formats ticks as FIX protocol messages, and streams them to `127.0.0.1:5000` via TCP. It runs in its own OS process — its GIL, GC pauses, and interpreter overhead are entirely isolated from the C++ measurement perimeter.

### Step 2 — Launch LLVM C++ Core

```bash
bin/Shaurya.exe        # Windows
./bin/Shaurya          # Linux
```

Startup sequence:
1. Parse `fdeep_model.json` → pre-allocate all neural network tensors
2. Warm L1/L2 instruction cache with inference dry runs
3. Initialize SPSC ring buffer with `alignas(64)` allocation
4. Pin execution thread to isolated CPU core
5. Begin live tick processing loop

### Step 3 — Benchmark (50 Stocks)

```bash
python benchmark_50.py --ticks 20
```

Injects 20 FIX messages per stock across a 50-stock basket. Outputs per-stock average, min, max, 90th/99th percentile latency, and aggregate statistics to both console and CSV. Fully automated — no human interaction required during the run.

### Step 4 — Review Metrics

After `Ctrl+C` shutdown, `SHAURYA_Metrics.txt` contains:
- Per-tick raw latency (µs)
- Average, 99th percentile, and tail latency
- Message throughput statistics

---

## 🔬 Technical Deep Dive

### Memory Hierarchy & Cache Management

SHAURYA's performance is fundamentally governed by cache residency. Key decisions:

- **`alignas(64)`** on all hot data structures — ensures each struct occupies exactly one or more full cache lines, preventing false sharing and structure-internal cache-line splits
- **NUMA-aware allocation** (Linux) — `numa_node_of_cpu()` is used to allocate ring buffer and neural network weights from the memory node local to the execution core, avoiding 50–100 ns remote memory access penalties on multi-socket servers
- **Software prefetching** — `_mm_prefetch` (Windows) / `__builtin_prefetch` (Linux) issues prefetch hints ~64 bytes ahead of the current neural network weight access, hiding DRAM latency by overlapping memory fetches with computation. The difference between cold and warm inference is up to 8 µs — making cache warming a mandatory startup step

### Thread Model & OS Interaction

- **Two-thread model:** Network receive thread (producer) and execution thread (consumer), each pinned to a dedicated logical core sharing the same L2/L3 but not hyper-threads
- **Real-time scheduling:** `SCHED_FIFO` priority 99 (Linux), `REALTIME_PRIORITY_CLASS` + `THREAD_PRIORITY_TIME_CRITICAL` (Windows) — reduces maximum latency spikes by ~40% compared to POSIX default scheduling
- **Socket configuration:** `TCP_NODELAY` (disables Nagle algorithm), `SO_RCVBUF` set to 8 MB — prevents TCP batching from introducing artificial latency on the loopback interface

### AI Model Static Compilation Pipeline

```
Keras (.h5)
    └─ frugally-deep converter
        └─ fdeep_model.json  (human-readable, ~500 KB for 128-64-1 net)
            └─ frugally-deep header-only parser (one-time at startup)
                └─ Eigen computational graph
                    └─ LLVM LTO + AVX2 → optimized binary
                        → < 1.2 µs inference, no GC, no Python
```

Weight updates (without architectural changes) only require replacing `fdeep_model.json` — no recompilation. Architectural changes require recompilation, which completes in seconds.

### Ablation Study Results

Disabling individual optimizations on the same bare-metal hardware:

| Configuration Removed | Avg Latency | Penalty |
|---|---|---|
| Full SHAURYA (baseline) | 4.22 µs | — |
| Static AI → TensorFlow | 89.6 µs | +2,023% |
| Zero-copy parser → std::string + stof | 28.4 µs | +573% |
| Lock-free SPSC → mutex queue | 12.8 µs | +203% |
| Branchless risk → if-statements | 6.1 µs | +45% |

Static AI compilation is the single largest contributor — TensorFlow's dynamic memory allocator introduces GC pauses that reach **4.1 ms** worst-case.

---

## ⚙️ Configuration

### Compiler Flags

```bash
-O3           # Aggressive optimization (loop unrolling, constant propagation)
-flto         # Link-Time Optimization (whole-program analysis)
-march=native # Target CPU's exact instruction set (AVX2, FMA, etc.)
-ffast-math   # Enable FMA fusion, reciprocal approximations
-fuse-ld=lld  # Use LLVM's lld linker for LTO compatibility
```

### System Tuning (Bare-Metal)

```bash
# Disable CPU power management
# BIOS: Disable C-states, SpeedStep, Turbo (or lock to max frequency)

# Windows
# Power plan: "Ultimate Performance"
# Set processor affinity to isolate cores 2-3 from OS interrupts

# Linux
echo performance | sudo tee /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor
sudo systemctl stop irqbalance
# Add to kernel boot params:
# isolcpus=2,3 nohz_full=2,3 rcu_nocbs=2,3
```

### Risk Gate Configuration

```cpp
RiskGate fatFinger(max_notional = 1'000'000);
RiskGate priceClamp(max_slippage_bps = 50);
RiskGate rateLimit(max_orders_per_second = 1000);
// Kill switch is always active and unconditional
```

---

## 🎯 Deployment Scenarios

**Bare-metal Windows/Linux workstation:**
- Sub-5 µs average latency achievable
- Minimum latency floor: ~1.75 µs (cache-primed, no OS interrupts)
- Suitable for: tick-by-tick strategies, momentum, market making research

**AWS EC2 shared instance:**
- Average ~36 µs, 99th percentile ~118 µs
- Hypervisor imposes a ~31.6 µs per-packet tax at the socket receive stage
- Suitable for: strategies with action intervals ≥ 100 ms, cloud-based backtesting

**AWS dedicated host / bare-metal cloud:**
- Hypervisor tax reduces to ~8–10 µs
- Suitable for: latency-sensitive cloud strategies without co-location budget

---

## 🚧 Limitations

**1. OS Scheduler Non-Determinism**
Neither Windows 11 nor standard Linux are real-time operating systems. Kernel timer interrupts and Deferred Procedure Calls (DPCs, Windows) can cause latency spikes of 127 µs (bare-metal) to 692 µs (AWS). Elimination requires PREEMPT_RT Linux, VxWorks, or bare-metal hypervisor deployment.

**2. Kernel-Space Networking**
SHAURYA uses standard POSIX/WinSock2 sockets. Each `recv()` call incurs a user-kernel context switch (~300–500 ns) plus a data copy from kernel to user space. Kernel bypass via DPDK would reduce receive latency to 300–500 ns but requires dedicated CPU cores and custom driver setup.

**3. Static Model Architecture**
The neural network architecture is fixed at compile time. Weight updates require only replacing the JSON file; layer changes require recompilation. JIT compilation via LLVM ORC APIs is a future direction.

**4. Single-Threaded Pipeline**
The current execution model pins the entire hot path to a single core. Parallelizing FIX parsing and inference across cores is future work.

**5. No Real Exchange Connectivity**
The current release targets research and simulation. Production connectivity (co-location, FIX drop-copy, exchange-specific protocols) is explicitly out of scope.

---

## 🚀 Roadmap

- [ ] DPDK kernel-bypass networking integration (`#ifdef USE_DPDK`)
- [ ] Native FPGA backend — synthesizable Verilog output from RTL firewall C++ source
- [ ] PREEMPT_RT Linux ultra-low-latency build
- [ ] GPU co-processor support (CUDA) for larger model architectures (LSTM, CNN-LSTM)
- [ ] JIT model reloading via LLVM ORC APIs
- [ ] Advanced order routing simulator with realistic fill modeling
- [ ] Hardware-in-the-Loop (HIL) extension: real FPGA risk gate via PCIe

---

## 🧪 Troubleshooting

**High latency spikes:**
- Verify CPU frequency scaling is disabled (`scaling_governor = performance`)
- Ensure LTO is enabled (`-flto` + `lld` linker)
- Confirm AVX2 availability: `grep avx2 /proc/cpuinfo`
- Disable Windows Defender real-time scanning and background services during benchmarks

**Model not loading:**
- Validate `fdeep_model.json` with frugally-deep's built-in checker
- Ensure the JSON path matches the compile-time configured default
- Check weight precision — frugally-deep expects `float32` by default

**Build failures:**
- Confirm Clang version: `clang++ --version` (≥ 14 recommended)
- Ensure `lld` is installed: `ld.lld --version`
- On Windows, verify LLVM is on `PATH` and not shadowed by MSVC toolchain
- Rebuild with `-v` flag for verbose compilation diagnostics

---

## ☢️ Disclaimer

SHAURYA is intended exclusively for:
- Academic research
- Systems engineering education
- HPC and compiler experimentation

It is **not financial advice** and **not production-certified trading infrastructure**. Users assume full responsibility for trading decisions, regulatory compliance, and capital risk. The RTL firewall has not undergone formal verification and should not be relied upon as the sole risk control in a live trading environment.

---

## 🔗 Links

- **PyPI:** [pypi.org/project/hft.shaurya](https://pypi.org/project/hft.shaurya)

## *ad astra per aspera 🛩️*
