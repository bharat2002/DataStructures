#include <iostream>
#include "Queue.h"
#include "Semaphore.h"
#include <list>
using namespace std;

BinarySemaphore sem;
void worker(int id) {
    std::cout << "Worker " << id << " waiting...\n";
    sem.wait();  // acquire
    std::cout << "Worker " << id << " entered critical section\n";

    std::this_thread::sleep_for(std::chrono::seconds(2));

    std::cout << "Worker " << id << " leaving critical section\n";
    sem.signal();  // release
}


ResettableEventCounter events;
std::list<int> eventList;
std::mutex listMutex;
void producer() {
    for (int i = 1; i <= 1000; i++) {
        {
            std::lock_guard<std::mutex> lock(listMutex);
            eventList.push_back(i);
            std::cout << "[Producer] Inserted event " << i << "\n";
        }
        events.signal();  // increment event count
        std::this_thread::sleep_for(std::chrono::milliseconds(15));
    }

    // simulate dropping signals mid-stream
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "[Producer] Resetting signals manually!\n";
    events.reset();
}

// --- Consumer thread ---
void consumer() {
    while (true) {
        events.wait_all();  // wait until some signals
        std::cout << "[Consumer] Woke up! (signals reset)\n";

        while (true) {
            int value = -1;
            {
                std::lock_guard<std::mutex> lock(listMutex);
                if (eventList.empty()) break;
                value = eventList.front();
                eventList.pop_front();
            }
            std::cout << "           Processed event " << value << "\n";
        }
    }
}

// --- Main test driver ---
int main() {
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    // let consumer keep running for demo
    std::this_thread::sleep_for(std::chrono::seconds(5));

    return 0;
}


/*
int main() {
    
    std::thread t1(worker, 1);
    std::thread t2(worker, 2);
    std::thread t3(worker, 3);
    t1.join();
    t2.join();
    t3.join();  
    /*CircularQueue<int> q(4);
    q.enqueue(10);
    cout << q.getFront() << " " << q.getRear() << endl;
    q.enqueue(20);
    cout << q.getFront() << " " << q.getRear() << endl;
    q.enqueue(30);
    cout << q.getFront() << " " << q.getRear() << endl;
    q.enqueue(40);
    cout << q.getFront() << " " << q.getRear() << endl;
    q.dequeue();
    cout << q.getFront() << " " << q.getRear() << endl;
    q.dequeue();
    cout << q.getFront() << " " << q.getRear() << endl;
        q.dequeue();
    cout << q.getFront() << " " << q.getRear() << endl;
    q.enqueue(50);
    cout << q.getFront() << " " << q.getRear() << endl;
    q.enqueue(50);
    q.enqueue(50);
    q.enqueue(50); 
    
    
//     return 0;
// }
// */