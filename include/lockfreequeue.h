#pragma once
#include <vector>
#include <atomic>

#define CACHELINE_SIZE 64

template<typename T, size_t Size>
class LockFreeQueue {
    std::vector<T> buffer;

    alignas(CACHELINE_SIZE) std::atomic<size_t> head; 
    
    char padding[CACHELINE_SIZE - sizeof(std::atomic<size_t>)]; 
    
    alignas(CACHELINE_SIZE) std::atomic<size_t> tail; 

public:
    LockFreeQueue() : buffer(Size) {
        head.store(0);
        tail.store(0);
    }

    bool push(const T& item) {
        size_t currentHead = head.load(std::memory_order_relaxed);
        size_t nextHead = (currentHead + 1) % Size;

        if (nextHead == tail.load(std::memory_order_acquire)) {
            return false; 
        }

        buffer[currentHead] = item;
        head.store(nextHead, std::memory_order_release);
        return true;
    }

    bool pop(T& item) {
        size_t currentTail = tail.load(std::memory_order_relaxed);
        if (currentTail == head.load(std::memory_order_acquire)) {
            return false; 
        }

        item = buffer[currentTail];
        tail.store((currentTail + 1) % Size, std::memory_order_release);
        return true;
    }
};