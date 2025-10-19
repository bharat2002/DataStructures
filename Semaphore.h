#pragma once
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
class BinarySemaphore {
private:
    std::condition_variable cv;
    std::mutex mtx;
    std::atomic_flag value;
public:
    BinarySemaphore()  {
        value.clear();
    }
    void wait() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this]() { return value.test(std::memory_order_acquire); });
        value.clear(std::memory_order_release);
    }
    void signal() {
        std::unique_lock<std::mutex> lock(mtx);
        value.test_and_set(std::memory_order_release);
        cv.notify_one();
    }
};

#include <atomic>
#include <condition_variable>
#include <mutex>

class ResettableEventCounter {
private:
    std::condition_variable m_cv;
    std::mutex m_mtx;
    std::atomic<int> m_count;   // still atomic, but all updates guarded by m_mtx

public:
    ResettableEventCounter() : m_count(0) {}

    // Wait for at least one event and consume one
    void wait() {
        std::unique_lock<std::mutex> lock(m_mtx);
        m_cv.wait(lock, [this]() { return m_count.load(std::memory_order_acquire) > 0; });

        // now safe to decrement while holding the lock
        m_count.store(m_count.load(std::memory_order_relaxed) - 1, std::memory_order_release);
    }

    // Wait until there is at least one event, then consume ALL
    int wait_all() {
        std::unique_lock<std::mutex> lock(m_mtx);
        m_cv.wait(lock, [this]() { return m_count.load(std::memory_order_acquire) > 0; });

        int consumed = m_count.load(std::memory_order_relaxed);
        m_count.store(0, std::memory_order_release);
        return consumed;
    }

    // Reset explicitly
    void reset() {
        std::lock_guard<std::mutex> lock(m_mtx);
        m_count.store(0, std::memory_order_release);
    }

    // Signal one new event
    void signal() {
        std::lock_guard<std::mutex> lock(m_mtx);
        m_count.store(m_count.load(std::memory_order_relaxed) + 1, std::memory_order_release);
        m_cv.notify_one();
    }

    // Optionally wake everyone (if multiple consumers wait)
    void signal_all() {
        std::lock_guard<std::mutex> lock(m_mtx);
        m_count.store(m_count.load(std::memory_order_relaxed) + 1, std::memory_order_release);
        m_cv.notify_all();
    }
};
