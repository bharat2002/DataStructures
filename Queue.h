
#include <iostream>
using namespace std;

template <typename T>
class CircularQueue {
private:
    T *arr;        
    int front, size; 
    int capacity;    

public:
    CircularQueue(int c) {
        arr = new T[c];
        capacity = c;
        front = size = 0; 
    }

    ~CircularQueue() {
        delete[] arr;
    }

    void enqueue(int x) {
        if (size == capacity) {
            cout << "Queue is full" << endl;
            return;
        }
        int rear = (front + size) % capacity;
        arr[rear] = x;
        size++;
    }

    void dequeue() {
        if (size == 0) {
            cout << "Queue is empty" << endl;
            return;
        }
        front = (front + 1) % capacity;
        size--;
    }

    int getFront() const {
        if (size == 0) {
            cout << "Queue is empty" << endl;
            return -1; 
        }
        return arr[front];
    }

    int getRear() const {
        if (size == 0) {
            cout << "Queue is empty" << endl;
            return -1; 
        }
        int rear = (front + size - 1) % capacity;
        return arr[rear];
    }
    int getSize() const {
        return size;
    }
    int getCapacity() const {
        return capacity;
    }
};

#include <atomic>
#include <cassert>
#include <cstddef>
#include <limits>
#include <new>
#include <utility>

template<typename T>
class SPSCQueue {
public:
    explicit SPSCQueue(size_t capacity_power_of_two) {
        assert((capacity_power_of_two & (capacity_power_of_two - 1)) == 0 &&
               "capacity must be power of two");
        capacity_ = capacity_power_of_two;
        mask_ = capacity_ - 1;

        buffer_ = static_cast<T*>(operator new[](sizeof(T) * capacity_));
        head_.store(0, std::memory_order_relaxed);
        tail_.store(0, std::memory_order_relaxed);
    }

    ~SPSCQueue() {
        size_t tail = tail_.load(std::memory_order_relaxed);
        size_t head = head_.load(std::memory_order_relaxed);
        while (tail != head) {
            T* slot = &buffer_[tail & mask_];
            slot->~T();
            tail = (tail + 1) & mask_;
        }
        operator delete[](buffer_);
    }

    SPSCQueue(const SPSCQueue&) = delete;
    SPSCQueue& operator=(const SPSCQueue&) = delete;

    bool try_push(const T& item) {
        size_t head = head_.load(std::memory_order_relaxed);
        size_t next = (head + 1) & mask_;
        size_t tail = tail_.load(std::memory_order_acquire);
        if (next == tail) return false;

        new (&buffer_[head]) T(item);
        head_.store(next, std::memory_order_release);
        return true;
    }

    bool try_push(T&& item) {
        size_t head = head_.load(std::memory_order_relaxed);
        size_t next = (head + 1) & mask_;
        size_t tail = tail_.load(std::memory_order_acquire);
        if (next == tail) return false;

        new (&buffer_[head]) T(std::move(item));
        head_.store(next, std::memory_order_release);
        return true;
    }

    bool try_pop(T& out) {
        size_t tail = tail_.load(std::memory_order_relaxed);
        size_t head = head_.load(std::memory_order_acquire);
        if (tail == head) return false;

        T* slot = &buffer_[tail];
        out = std::move(*slot);
        slot->~T();
        tail_.store((tail + 1) & mask_, std::memory_order_release);
        return true;
    }

    size_t capacity() const noexcept { return capacity_; }

private:
    T* buffer_;               // raw buffer
    size_t capacity_;
    size_t mask_;

    alignas(64) std::atomic<size_t> head_;
    alignas(64) std::atomic<size_t> tail_;
};
