# SHAURYA: Scalable High-frequency Architecture for Ultra-low Response Yield Access

![Language](https://img.shields.io/badge/language-C%2B%2B17-blue.svg)
![Latency](https://img.shields.io/badge/min%20latency-300%20ns-brightgreen.svg)
![Architecture](https://img.shields.io/badge/architecture-Lock--Free-orange.svg)
![Parsing](https://img.shields.io/badge/parsing-Zero--Copy-red.svg)

**Shaurya** is a high-frequency trading (HFT) market data feed handler engineered for sub-microsecond latency. By leveraging **Zero-Copy parsing**, **Lock-Free concurrency**, and **Stack-based memory management**, it bypasses the performance bottlenecks of standard software architectures to process financial data with deterministic speed.

---

## ⚡ Performance Impact & Comparison

Shaurya was benchmarked using high-resolution hardware timers (`QueryPerformanceCounter`).

| Implementation Approach | Average Latency | Min Latency | Why it's Slow/Fast? |
| :--- | :--- | :--- | :--- |
| **Python Script** | ~45.0 µs | ~30.0 µs | Interpreter overhead & Garbage Collection pauses. |
| **Standard C++ (`std::string`)** | ~5.0 µs | ~3.5 µs | Frequent Heap Allocations (`malloc`) & deep memory copying. |
| **SHAURYA (Zero-Copy)** | **1.88 µs*** | **0.3 µs** | **Zero-Copy** pointer arithmetic & **Lock-Free** queues. |

> **The Result:** Shaurya achieves a minimum internal reaction time of **300 nanoseconds**, approximately **50x faster** than standard Python implementations.
>
> **Measured in Pure Mock Environment*

![WhatsApp Image 2025-12-12 at 23 55 35_9e0c137d](https://github.com/user-attachments/assets/c095eb1a-0a6b-40d3-8a43-8a725090134b)


### 🌍 Real-World Validation: The "Fragmented Liquidity" Test
Shaurya was subjected to a **30-minute stress test** aggregating live ticks from **Binance, Coinbase, and Bitstamp** simultaneously.

* **Test Duration:** 30 Minutes
* **Total Messages:** 21,862 (Live Volatility Bursts)
* **Outcome:** The engine successfully normalized fragmented liquidity streams in real-time. While average latency increased under OS scheduler load (due to non-isolated cores), the **minimum latency remained at 0.3 µs**, proving the core engine's efficiency remains stable even during crypto market volatility.

---

## 🏗 Key Technical Innovations

### 1. Zero-Copy Architecture
Instead of copying network packets into new `std::string` objects (which forces the OS to allocate memory), Shaurya uses a custom `StringViewLite` class. This creates a lightweight "view" over the raw socket buffer, allowing the engine to parse prices without moving a single byte of memory.

### 2. Lock-Free Concurrency (SPSC)
Traditional systems use Mutex locks (`std::mutex`) to share data between threads, which forces the CPU to stop and switch contexts (expensive). Shaurya implements a **Single-Producer Single-Consumer Ring Buffer** using `std::atomic` instructions. This allows the Network Thread to push data and the Strategy Thread to read data simultaneously without ever blocking.

### 3. CPU Cache Optimization
Critical data structures are aligned to 64-byte cache lines (`alignas(64)`). This prevents **False Sharing**, a phenomenon where two threads fight over the same CPU cache line, drastically reducing performance on multi-core systems.

---

## 🚀 Quick Start

### Prerequisites
* **OS:** Windows (Required for `winsock2` and `QueryPerformanceCounter`)
* **Compiler:** G++ (MinGW) supporting C++11 or higher.

### Execution Guide
1.  **Build the System:**
    ```cmd
    build.bat
    ```
2.  **Start Data Source:** 
    ```python bridge.py```
3.  **Start Shaurya Engine:**
    ```cmd
    bin\Shaurya.exe
    ```

*Upon completion, the engine generates a `Shaurya_Metrics.txt` report detailing the nanosecond-level performance of the run.*

---

## Resources

If you are new to High-Frequency Trading systems, these concepts explain the "Why" behind Shaurya's architecture:

* **Latency vs. Jitter:** [Understand why "Average Speed" is useless in HFT](https://www.youtube.com/watch?v=NH1Tta7purM).
* **Zero-Copy Networking:** [How avoiding memory copies saves microseconds](https://en.wikipedia.org/wiki/Zero-copy).
* **Lock-Free Programming:** [An introduction to Atomics and Ring Buffers](https://www.1024cores.net/home/lock-free-algorithms/queues).
* **False Sharing:** [The hidden killer of multi-threaded performance](https://mechanical-sympathy.blogspot.com/2011/07/false-sharing.html).

`Developed by your's truly 🛩️!`