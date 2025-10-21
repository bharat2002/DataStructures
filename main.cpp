#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <atomic>
#include "Queue/Queue.h" // Your queue interface and ThreadSafeQueue implementation

using namespace std;
using namespace std::chrono;

// Producer thread function
void producer(QueueInterface* queue, int numOps) {
    for (int i = 0; i < numOps; ++i) {
        queue->enqueue(i);
    }
}

// Consumer thread function (safe version)
void consumer(QueueInterface* queue, int numOps) {
    int completed = 0;
    while (completed < numOps) {
        try {
            queue->dequeue();
            ++completed;
        } catch (const std::underflow_error&) {
            // Queue is temporarily empty, yield and retry
            std::this_thread::yield();
        }
    }
}

int main() {
    const int NUM_PRODUCERS = 8;     // number of producer threads
    const int NUM_CONSUMERS = 8;     // number of consumer threads
    const int OPS_PER_THREAD = 1000000; // enqueue/dequeue ops per thread

    QueueInterface* queue = new ThreadSafeQueue();

    cout << "Benchmarking ThreadSafeQueue..." << endl;
    cout << "Producers: " << NUM_PRODUCERS << ", Consumers: " << NUM_CONSUMERS << endl;
    cout << "Operations per thread: " << OPS_PER_THREAD << endl;

    // Pre-fill the queue a bit to reduce early underflow
    for (int i = 0; i < NUM_CONSUMERS * 100; ++i) {
        queue->enqueue(i);
    }

    auto start = high_resolution_clock::now();

    vector<thread> producers, consumers;

    // Launch producers
    for (int i = 0; i < NUM_PRODUCERS; ++i) {
        producers.emplace_back(producer, queue, OPS_PER_THREAD);
    }

    // Launch consumers
    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        consumers.emplace_back(consumer, queue, OPS_PER_THREAD);
    }

    // Join all threads
    for (auto& t : producers) t.join();
    for (auto& t : consumers) t.join();

    auto end = high_resolution_clock::now();
    double duration = duration_cast<milliseconds>(end - start).count();

    long long totalOps = (NUM_PRODUCERS + NUM_CONSUMERS) * OPS_PER_THREAD;
    double opsPerSec = (totalOps / duration) * 1000.0;

    cout << "Total operations: " << totalOps << endl;
    cout << "Total time: " << duration << " ms" << endl;
    cout << "Throughput: " << opsPerSec << " ops/sec" << endl;

    delete queue;
    return 0;
}
