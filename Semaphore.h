#pragma once
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

class BinarySemaphore {
private:
    std::condition_variable cv;
    std::mutex mtx;
    bool value;
public:
    BinarySemaphore() : value(1) {

    }
    void wait() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this]() { return value; });
        value = 0;
    }
    void signal() {
        std::unique_lock<std::mutex> lock(mtx);
        value = 1;
        cv.notify_one();
    }
};

class ResettableEventCounter {
private:
    std::condition_variable m_cv;
    std::mutex m_mtx;
    int m_count;
public:
    ResettableEventCounter() : m_count(0) {}
    void wait() {
        std::unique_lock<std::mutex> lock(m_mtx);
        m_cv.wait(lock, [this]() { return m_count > 0; });
        --m_count;
    }

    void wait_all()
    {
        std::unique_lock<std::mutex> lock(m_mtx);
        m_cv.wait(lock, [this]() { return m_count > 0; });
        m_count = 0; //resetting the count var to zero 
    }

    void reset() 
    {
        std::unique_lock<std::mutex> lock(m_mtx);
        m_count = 0;
    }

    void signal() {
        std::unique_lock<std::mutex> lock(m_mtx);
        ++m_count;
        m_cv.notify_one();
    }

};